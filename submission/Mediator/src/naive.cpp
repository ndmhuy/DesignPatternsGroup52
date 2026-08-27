#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace naive {

enum class FlightStatus {
    IN_FLIGHT,
    HOLDING_PATTERN,
    ON_RUNWAY,
    LANDED,
    PARKED_AT_GATE
};

enum class FlightType {
    COMMERCIAL,
    CARGO,
    EMERGENCY
};

inline std::string statusToString(FlightStatus s) {
    switch (s) {
        case FlightStatus::IN_FLIGHT:       return "IN_FLIGHT";
        case FlightStatus::HOLDING_PATTERN: return "HOLDING_PATTERN";
        case FlightStatus::ON_RUNWAY:       return "ON_RUNWAY";
        case FlightStatus::LANDED:          return "LANDED";
        case FlightStatus::PARKED_AT_GATE:  return "PARKED_AT_GATE";
    }
    return "UNKNOWN";
}

inline std::string typeToString(FlightType t) {
    switch (t) {
        case FlightType::COMMERCIAL: return "Commercial";
        case FlightType::CARGO:      return "Cargo";
        case FlightType::EMERGENCY:  return "Emergency";
    }
    return "Unknown";
}

class NaiveFlight {
private:
    std::string flightCode_;
    FlightType type_;
    FlightStatus status_;
    int capacityOrWeight_; // Passengers for commercial, tons for cargo
    
    // Tightly coupled: Every flight maintains direct pointers to all other active peers in airspace (O(N^2) mesh)
    std::vector<NaiveFlight*> peerNetwork_;

public:
    NaiveFlight(std::string code, FlightType type, int capacityOrWeight)
        : flightCode_(std::move(code)),
          type_(type),
          status_(FlightStatus::IN_FLIGHT),
          capacityOrWeight_(capacityOrWeight) {}

    ~NaiveFlight() {
        // RAII Guard: Must unhook from all peers if destroyed while in airspace
        leaveAirspaceNetwork();
    }

    // Getters
    const std::string& getCode() const { return flightCode_; }
    FlightType getType() const { return type_; }
    FlightStatus getStatus() const { return status_; }
    int getCapacityOrWeight() const { return capacityOrWeight_; }
    size_t getPeerCount() const { return peerNetwork_.size(); }

    void addPeer(NaiveFlight* peer) {
        if (peer != this && std::find(peerNetwork_.begin(), peerNetwork_.end(), peer) == peerNetwork_.end()) {
            peerNetwork_.push_back(peer);
        }
    }

    void removePeer(NaiveFlight* peer) {
        peerNetwork_.erase(
            std::remove(peerNetwork_.begin(), peerNetwork_.end(), peer),
            peerNetwork_.end()
        );
    }

    // Joins airspace: Wires this flight to all current flights, and all current flights to this flight
    void joinAirspaceNetwork(std::vector<NaiveFlight*>& currentAirspace) {
        for (auto* peer : currentAirspace) {
            this->addPeer(peer);
            peer->addPeer(this); // Bidirectional mutual registration
        }
        currentAirspace.push_back(this);
        std::cout << "[" << flightCode_ << " (" << typeToString(type_) << ")] Entered airspace. "
                  << "Established mutual P2P links with " << peerNetwork_.size() << " peers.\n";
    }

    // Leaves airspace (e.g. after parking at gate): Must notify and unhook from every peer
    void leaveAirspaceNetwork() {
        if (peerNetwork_.empty()) return;

        std::cout << "[" << flightCode_ << "] Exiting active airspace. Executing O(N) unregistration sweep across "
                  << peerNetwork_.size() << " peers...\n";
        for (auto* peer : peerNetwork_) {
            peer->removePeer(this); // Mutate peer's internal collection
        }
        peerNetwork_.clear();
    }

    void receiveRadioMessage(const std::string& from, const std::string& msg) {
        std::cout << "  [" << flightCode_ << " Radio] From " << from << ": " << msg << "\n";
    }

    void broadcastToPeers(const std::string& msg) {
        for (auto* peer : peerNetwork_) {
            peer->receiveRadioMessage(flightCode_, msg);
        }
    }

    // Decentralized consensus algorithm: The flight polls all peers to determine if it is safe to land
    bool requestLandingPermission() {
        std::cout << "[" << flightCode_ << " (" << typeToString(type_) << ")] Requesting landing permission by polling "
                  << peerNetwork_.size() << " peers...\n";

        for (auto* peer : peerNetwork_) {
            // Check 1: Is any peer currently occupying the runway?
            if (peer->getStatus() == FlightStatus::ON_RUNWAY) {
                status_ = FlightStatus::HOLDING_PATTERN;
                std::cout << "  -> CONFLICT: Peer " << peer->getCode() 
                          << " is currently ON_RUNWAY. Entering " << statusToString(status_) << ".\n";
                return false;
            }

            // Check 2: Does an emergency peer have priority?
            if (type_ != FlightType::EMERGENCY && peer->getType() == FlightType::EMERGENCY &&
                (peer->getStatus() == FlightStatus::HOLDING_PATTERN || peer->getStatus() == FlightStatus::IN_FLIGHT)) {
                status_ = FlightStatus::HOLDING_PATTERN;
                std::cout << "  -> PRIORITY YIELD: Emergency peer " << peer->getCode() 
                          << " has airspace priority. Entering " << statusToString(status_) << ".\n";
                return false;
            }
        }

        // Consensus reached
        status_ = FlightStatus::ON_RUNWAY;
        std::cout << "  -> CONSENSUS APPROVED: All " << peerNetwork_.size() 
                  << " peers report runway clear. Status: " << statusToString(status_) << ".\n";
        broadcastToPeers("Acquired runway 07L for landing approach.");
        return true;
    }

    void touchdown() {
        if (status_ != FlightStatus::ON_RUNWAY) {
            std::cout << "[" << flightCode_ << "] Cannot touchdown without runway acquisition!\n";
            return;
        }
        status_ = FlightStatus::LANDED;
        std::cout << "[" << flightCode_ << "] >>> TOUCHDOWN SUCCESSFUL on Runway 07L. Status: " 
                  << statusToString(status_) << ".\n";
    }

    void parkAtGateAndExitAirspace(std::vector<NaiveFlight*>& airspaceRegistry) {
        status_ = FlightStatus::PARKED_AT_GATE;
        std::cout << "[" << flightCode_ << "] Parked at terminal gate. Status: " 
                  << statusToString(status_) << ".\n";
        
        // Remove from global registry
        airspaceRegistry.erase(
            std::remove(airspaceRegistry.begin(), airspaceRegistry.end(), this),
            airspaceRegistry.end()
        );

        // Perform mutual unregistration sweep
        leaveAirspaceNetwork();
    }
};

} // namespace naive

void runNaiveDemo() {
    std::cout << "\n=== RUNNING MEDIATOR NAIVE DEMO (Without Pattern - Decentralized Mesh) ===\n";
    std::vector<naive::NaiveFlight*> airspaceRegistry;

    // Step 1: Initial flights enter airspace
    naive::NaiveFlight f1("VN123", naive::FlightType::COMMERCIAL, 180);
    naive::NaiveFlight f2("AF456", naive::FlightType::COMMERCIAL, 220);
    naive::NaiveFlight f3("BA789", naive::FlightType::COMMERCIAL, 250);

    f1.joinAirspaceNetwork(airspaceRegistry);
    f2.joinAirspaceNetwork(airspaceRegistry);
    f3.joinAirspaceNetwork(airspaceRegistry);

    std::cout << "\nTotal active flights: " << airspaceRegistry.size() 
              << " | Total P2P connections: " << (3 * 2) << " (O(N^2) mesh network)\n\n";

    // Step 2: VN123 requests landing
    std::cout << "--- Step 1: Flight VN123 Requests Landing ---\n";
    f1.requestLandingPermission();

    // Step 3: AF456 requests landing while VN123 is on runway
    std::cout << "\n--- Step 2: Flight AF456 Requests Landing (Runway Occupied) ---\n";
    f2.requestLandingPermission(); // Rejects and changes state to HOLDING_PATTERN

    // Step 4: Adding a 4th flight (FX902 Cargo) requires N-way mutual wiring
    std::cout << "\n--- Step 3: Adding 4th Flight FX902 (Cargo) ---\n";
    naive::NaiveFlight f4("FX902", naive::FlightType::CARGO, 60);
    f4.joinAirspaceNetwork(airspaceRegistry);
    std::cout << "Total active flights: " << airspaceRegistry.size() 
              << " | Total P2P connections grew to: " << (4 * 3) << " (12 connections)\n";

    // Step 5: VN123 completes landing, parks at gate, and unhooks from all peers
    std::cout << "\n--- Step 4: Flight VN123 Completes Landing & Parks at Gate ---\n";
    f1.touchdown();
    f1.parkAtGateAndExitAirspace(airspaceRegistry);

    // Step 6: AF456 retries landing now that VN123 has vacated and unhooked
    std::cout << "\n--- Step 5: Flight AF456 Retries Landing after VN123 Exited Airspace ---\n";
    f2.requestLandingPermission(); // Now succeeds
    f2.touchdown();
    f2.parkAtGateAndExitAirspace(airspaceRegistry);

    // Step 7: Remaining flights park and exit
    std::cout << "\n--- Step 6: Remaining Flights (BA789, FX902) Park at Gate ---\n";
    f3.parkAtGateAndExitAirspace(airspaceRegistry);
    f4.parkAtGateAndExitAirspace(airspaceRegistry);

    std::cout << "\nNotice the design drawbacks in Naive Solution:\n"
              << " 1. Single Responsibility Principle (SRP) Violated: Flight objects must manage peer meshes and airspace consensus.\n"
              << " 2. Open-Closed Principle (OCP) Violated: Adding new coordination rules requires editing consensus loops in all flights.\n"
              << " 3. O(N^2) Connection Complexity: Every flight entry/exit ripples across every other active flight object.\n";

    std::cout << "=== MEDIATOR NAIVE DEMO COMPLETED ===\n";
}


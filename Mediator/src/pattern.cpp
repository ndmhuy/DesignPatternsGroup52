#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

namespace pattern {

class Flight; // Forward declaration

// Abstract Mediator Interface
class IATCMediator {
public:
    virtual ~IATCMediator() = default;
    virtual void registerFlight(std::shared_ptr<Flight> flight) = 0;
    virtual bool requestLanding(Flight* flight) = 0;
    virtual void notifyRunwayClear(Flight* flight) = 0;
    virtual void broadcastEmergency(Flight* flight, const std::string& reason) = 0;
};

// Colleague Base Class
class Flight {
protected:
    IATCMediator* mediator_;
    std::string flightCode_;

public:
    Flight(std::string code, IATCMediator* mediator)
        : mediator_(mediator), flightCode_(std::move(code)) {}
    virtual ~Flight() = default;

    const std::string& getCode() const { return flightCode_; }

    virtual bool requestLanding() {
        std::cout << "[" << flightCode_ << "] Requesting landing clearance from ATC Tower...\n";
        return mediator_->requestLanding(this);
    }

    virtual void land() {
        std::cout << "[" << flightCode_ << "] >>> TOUCHDOWN SUCCESSFUL on Runway 07L. Clearing runway...\n";
        mediator_->notifyRunwayClear(this);
    }

    virtual void receiveMessage(const std::string& from, const std::string& msg) {
        std::cout << "  [" << flightCode_ << " Radio] Received from " << from << ": " << msg << "\n";
    }
};

// Concrete Colleague: Commercial Passenger Flight
class CommercialFlight : public Flight {
private:
    int passengerCount_;

public:
    CommercialFlight(std::string code, int passengers, IATCMediator* mediator)
        : Flight(std::move(code), mediator), passengerCount_(passengers) {}

    bool requestLanding() override {
        std::cout << "[" << flightCode_ << " (Commercial - " << passengerCount_ << " passengers)] "
                  << "Approaching airport. Requesting landing clearance...\n";
        return mediator_->requestLanding(this);
    }
};

// Concrete Colleague: Cargo Freight Flight
class CargoFlight : public Flight {
private:
    double cargoWeightTons_;

public:
    CargoFlight(std::string code, double cargoTons, IATCMediator* mediator)
        : Flight(std::move(code), mediator), cargoWeightTons_(cargoTons) {}

    bool requestLanding() override {
        std::cout << "[" << flightCode_ << " (Cargo - " << cargoWeightTons_ << " tons)] "
                  << "Heavy transport on final approach. Requesting landing clearance...\n";
        return mediator_->requestLanding(this);
    }
};

// Concrete Colleague: Emergency Flight (Air Ambulance / Medevac)
class EmergencyFlight : public Flight {
public:
    using Flight::Flight;

    void declareEmergency(const std::string& reason) {
        std::cout << "\n[" << flightCode_ << " (EMERGENCY)] !!! MAYDAY MAYDAY MAYDAY: " << reason << " !!!\n";
        mediator_->broadcastEmergency(this, reason);
    }
};

// Concrete Mediator: Air Traffic Control Tower
class ATCTower : public IATCMediator {
private:
    bool runwayClear_ = true;
    Flight* currentRunwayUser_ = nullptr;
    std::queue<Flight*> landingQueue_;
    std::vector<std::shared_ptr<Flight>> activeAirspaceFlights_;

public:
    void registerFlight(std::shared_ptr<Flight> flight) override {
        activeAirspaceFlights_.push_back(flight);
        std::cout << "[ATC Tower] Radar tracked: Flight " << flight->getCode() 
                  << " entered airspace and registered with tower.\n";
    }

    bool requestLanding(Flight* flight) override {
        if (runwayClear_) {
            runwayClear_ = false;
            currentRunwayUser_ = flight;
            std::cout << "[ATC Tower] Clearance GRANTED for " << flight->getCode() 
                      << ". Runway 07L is CLEAR for landing.\n";
            return true;
        } else {
            landingQueue_.push(flight);
            std::cout << "[ATC Tower] HOLDING PATTERN for " << flight->getCode() 
                      << ". Runway 07L currently OCCUPIED by " << currentRunwayUser_->getCode() 
                      << ". Added to queue (Queue position: " << landingQueue_.size() << ").\n";
            return false;
        }
    }

    void notifyRunwayClear(Flight* flight) override {
        if (currentRunwayUser_ == flight) {
            std::cout << "[ATC Tower] Runway 07L VACATED by " << flight->getCode() << ".\n";
            currentRunwayUser_ = nullptr;
            runwayClear_ = true;

            // Automatically dispatch the next flight waiting in queue
            if (!landingQueue_.empty()) {
                Flight* nextFlight = landingQueue_.front();
                landingQueue_.pop();
                std::cout << "[ATC Tower] Calling next queued flight: Clearance GRANTED for " 
                          << nextFlight->getCode() << ".\n";
                runwayClear_ = false;
                currentRunwayUser_ = nextFlight;
                nextFlight->land();
            } else {
                std::cout << "[ATC Tower] Runway 07L is currently IDLE and ready for traffic.\n";
            }
        }
    }

    void broadcastEmergency(Flight* emergencyFlight, const std::string& reason) override {
        std::cout << "[ATC Tower ALERT] Priority Emergency declared by " << emergencyFlight->getCode() 
                  << " (" << reason << "). Cleared for IMMEDIATE priority landing!\n";
        
        // Broadcast safety alert to all other flights in airspace
        for (const auto& f : activeAirspaceFlights_) {
            if (f.get() != emergencyFlight) {
                f->receiveMessage("ATC Tower", "AIRSPACE ADVISORY: Yield runway for emergency flight " 
                                  + emergencyFlight->getCode() + " (" + reason + ").");
            }
        }

        // Fast-track emergency landing
        runwayClear_ = false;
        currentRunwayUser_ = emergencyFlight;
        emergencyFlight->land();
    }
};

} // namespace pattern

void runPatternDemo() {
    std::cout << "\n=== RUNNING MEDIATOR PATTERN DEMO (With ATCTower Mediator) ===\n";
    
    // Step 1: Initialize the Central Mediator (ATC Tower)
    auto tower = std::make_shared<pattern::ATCTower>();
    std::cout << "ATC Tower (Central Mediator) online.\n\n";

    // Step 2: Create flights with a reference ONLY to the Mediator (0 peer-to-peer coupling)
    auto vn123 = std::make_shared<pattern::CommercialFlight>("VN123", 180, tower.get());
    auto fx902 = std::make_shared<pattern::CargoFlight>("FX902", 45.5, tower.get());
    auto ba789 = std::make_shared<pattern::CommercialFlight>("BA789", 250, tower.get());

    tower->registerFlight(vn123);
    tower->registerFlight(fx902);
    tower->registerFlight(ba789);

    std::cout << "\n--- Scenario 1: Flight VN123 Requests Landing (Runway Free) ---\n";
    vn123->requestLanding(); // Granted, now on runway approach

    std::cout << "\n--- Scenario 2: Flights FX902 and BA789 Request Landing (Queued in Holding Pattern) ---\n";
    fx902->requestLanding(); // Held in queue #1
    ba789->requestLanding(); // Held in queue #2

    std::cout << "\n--- Scenario 3: Flight VN123 Touches Down & Vacates Runway (Automatic Cascade) ---\n";
    vn123->land(); // Vacates -> ATC grants FX902 -> FX902 lands & vacates -> ATC grants BA789 -> BA789 lands & vacates

    std::cout << "\n--- Scenario 4: Emergency Flight MEDIC1 Mayday Broadcast ---\n";
    auto medevac = std::make_shared<pattern::EmergencyFlight>("MEDIC1", tower.get());
    tower->registerFlight(medevac);
    medevac->declareEmergency("Critical Patient on Board / Low Fuel");

    std::cout << "\n=== MEDIATOR PATTERN DEMO COMPLETED ===\n";
}

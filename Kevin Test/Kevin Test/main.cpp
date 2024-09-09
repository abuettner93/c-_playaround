#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Cargo class - just a container for a name and weight
class Cargo {
public:
    string type;
    double weight;

    Cargo(string type, double weight) : type(type), weight(weight) {}
};

// Person class - just a container for a name and height
class Person {
public:
    string name;
    double height;

    Person(string name, double height) : name(name), height(height) {}
};

// Interface/Abstract Transporter class
class Transporter {
    // note that the public component of this class is just virtual functions that arent really defined. Placeholders, really.
    // I think I could add a non-virtual function here that WOULDNT require overriding, and the inheriting class would just use it.
public:
    virtual void load() = 0;
    virtual void unload() = 0;
    virtual void empty() = 0;
    virtual bool isEmpty() = 0;
    virtual int itemsCount() = 0;
    virtual void move() = 0;
};

// Train class (inherits from Transporter)
class Train : public Transporter {
private:
    vector<Cargo> cargo;
public:
    void load() override {
        string type;
        double weight;
        cout << "Enter cargo type: ";
        cin >> type;
        cout << "Enter cargo weight: ";
        cin >> weight;
        cargo.push_back(Cargo(type, weight));
    }

    void unload() override {
        if (!cargo.empty()) {
            cout << "Unloading cargo of type: " << cargo.back().type << " and weight: " << cargo.back().weight << endl;
            cargo.pop_back();
        } else {
            cout << "No cargo to unload." << endl;
        }
    }

    void empty() override {
        cargo.clear();
        cout << "All cargo has been emptied." << endl;
    }

    bool isEmpty() override {
        return cargo.empty();
    }

    int itemsCount() override {
        return cargo.size();
    }

    double totalWeight() {
        double weight = 0;
        for (auto &c : cargo) {
            weight += c.weight;
        }
        return weight;
    }

    void move() override {
        cout << "Train has reached the next destination." << endl;
    }
};

// Bus class (inherits from Transporter - note that the functions of transporter are overridden, but MUST exist or the code fails to compile)
class Bus : public Transporter {
private:
    vector<Person> passengers;
    double fare;

public:
    // I guess this initializes the Bus class, and sets a default fare as 2.0.
    // it feels weird that c++ requires you to initialize the class on/during its call, but I guess its not that strange.
    Bus() : fare(2.0) {}

    void load() override {
        string name;
        double height;
        cout << "Enter passenger name: ";
        cin >> name;
        cout << "Enter passenger height: ";
        cin >> height;
        // adds a passenger (Person) object to the passenger vector. push_back is a built in vector function.
        passengers.push_back(Person(name, height));

        // Sort passengers by height (shortest to tallest) (thanks ChatGPT, this is weird as shit and feels complex)
        sort(passengers.begin(), passengers.end(), [](Person &a, Person &b) {
            return a.height < b.height;
        });
    }

    void unload() override {
        if (!passengers.empty()) {
            // passengers.back gets the person who got on first? Idk, it just seems to be going back in the list.
            cout << "Unloading passenger: " << passengers.back().name << endl;
            // pop_back is a vector function
            passengers.pop_back();
        } else {
            cout << "No passengers to unload." << endl;
        }
    }

    void empty() override {
        passengers.clear();
        cout << "All passengers have been unloaded." << endl;
    }

    bool isEmpty() override {
        return passengers.empty();
    }

    int itemsCount() override {
        // Xcode keeps telling me this has some implicit conversion thing going on but the code works, so... meh)
        return passengers.size();
    }

    double totalFare() {
        return passengers.size() * fare;
    }

    void setFare(double newFare) {
        // for those greedy bus drivers
        fare = newFare;
    }

    void move() override {
        // Lol this seems shitty, but I guess moving could be elaborated on to be more than just a print.
        // For example, the bus moves to a station object. Who knows, maybe thatll be next assignment.
        cout << "Bus has reached the next stop." << endl;
    }
};

// Main driver function
int main() {
    // Create a train and a bus
    Train train;
    Bus bus;

    // Load some cargo onto the train
    cout << "Loading cargo onto the train..." << endl;
    train.load();
    train.load();

    cout << "Total weight of cargo on the train: " << train.totalWeight() << " kg" << endl;

    // Move the train
    train.move();

    // Unload some cargo from the train
    train.unload();
    cout << "Items remaining in the train: " << train.itemsCount() << endl;

    // Load some passengers onto the bus
    cout << "\nLoading passengers onto the bus..." << endl;
    bus.load();
    bus.load();

    // Move the bus
    bus.move();

    // Set fare and display total fare
    bus.setFare(3.0); // Changing the fare
    cout << "Total fare for passengers: $" << bus.totalFare() << endl;

    // Unload passengers from the bus
    bus.unload();
    cout << "Passengers remaining on the bus: " << bus.itemsCount() << endl;

    return 0;
}

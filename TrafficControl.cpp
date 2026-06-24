#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Structure to store traffic data (Lane-based)
struct Traffic {
    string time;
    int lane1;
    int lane2;
    int total;
};

// Function to calculate total vehicles
int calculateTotal(Traffic t[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += t[i].total;
    }
    return sum;
}

// Function to find peak traffic index
int findPeakIndex(Traffic t[], int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; i++) {
        if (t[i].total > t[maxIndex].total) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Function to classify traffic
string classifyTraffic(int vehicles) {
    if (vehicles < 30)
        return "Light";
    else if (vehicles < 70)
        return "Moderate";
    else
        return "Heavy";
}

// Function to detect congestion
void detectCongestion(Traffic t[], int size) {
    cout << "\n=== Congestion Periods ===\n";
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (t[i].total > 80) {
            cout << t[i].time << " (Very Heavy Traffic)\n";
            found = true;
        }
    }
    if (!found)
        cout << "No congestion detected.\n";
}

int main() {
    const int SIZE = 10;

    Traffic roadA[SIZE];
    Traffic roadB[SIZE];

    cout << "=== Traffic Flow Monitoring System ===\n";

    // Input for Road A
    cout << "\n--- Input Data for Road A ---\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "\nEnter time (e.g. 8AM): ";
        cin >> roadA[i].time;

        // Lane 1 validation
        do {
            cout << "Lane 1 vehicles: ";
            cin >> roadA[i].lane1;
            if (roadA[i].lane1 < 0)
                cout << "Invalid! Enter positive value.\n";
        } while (roadA[i].lane1 < 0);

        // Lane 2 validation
        do {
            cout << "Lane 2 vehicles: ";
            cin >> roadA[i].lane2;
            if (roadA[i].lane2 < 0)
                cout << "Invalid! Enter positive value.\n";
        } while (roadA[i].lane2 < 0);

        roadA[i].total = roadA[i].lane1 + roadA[i].lane2;
    }

    // Input for Road B (BONUS)
    cout << "\n--- Input Data for Road B ---\n";
    for (int i = 0; i < SIZE; i++) {
        roadB[i].time = roadA[i].time; // same time

        do {
            cout << "Road B - Lane 1 vehicles: ";
            cin >> roadB[i].lane1;
            if (roadB[i].lane1 < 0)
                cout << "Invalid!\n";
        } while (roadB[i].lane1 < 0);

        do {
            cout << "Road B - Lane 2 vehicles: ";
            cin >> roadB[i].lane2;
            if (roadB[i].lane2 < 0)
                cout << "Invalid!\n";
        } while (roadB[i].lane2 < 0);

        roadB[i].total = roadB[i].lane1 + roadB[i].lane2;
    }

    // Calculations
    int totalA = calculateTotal(roadA, SIZE);
    int totalB = calculateTotal(roadB, SIZE);

    int peakA = findPeakIndex(roadA, SIZE);
    int peakB = findPeakIndex(roadB, SIZE);

    // Output Road A
    cout << "\n===== ROAD A REPORT =====\n";
    cout << left << setw(10) << "Time"
         << setw(10) << "L1"
         << setw(10) << "L2"
         << setw(10) << "Total"
         << setw(15) << "Category" << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << left << setw(10) << roadA[i].time
             << setw(10) << roadA[i].lane1
             << setw(10) << roadA[i].lane2
             << setw(10) << roadA[i].total
             << setw(15) << classifyTraffic(roadA[i].total)
             << endl;
    }

    cout << "\nTotal Vehicles (Road A): " << totalA << endl;
    cout << "Peak Time (Road A): " << roadA[peakA].time
         << " (" << roadA[peakA].total << " vehicles)\n";

    // Output Road B
    cout << "\n===== ROAD B REPORT =====\n";
    cout << left << setw(10) << "Time"
         << setw(10) << "L1"
         << setw(10) << "L2"
         << setw(10) << "Total"
         << setw(15) << "Category" << endl;

    for (int i = 0; i < SIZE; i++) {
        cout << left << setw(10) << roadB[i].time
             << setw(10) << roadB[i].lane1
             << setw(10) << roadB[i].lane2
             << setw(10) << roadB[i].total
             << setw(15) << classifyTraffic(roadB[i].total)
             << endl;
    }

    cout << "\nTotal Vehicles (Road B): " << totalB << endl;
    cout << "Peak Time (Road B): " << roadB[peakB].time
         << " (" << roadB[peakB].total << " vehicles)\n";

    // Compare roads (BONUS)
    cout << "\n===== COMPARISON =====\n";
    if (totalA > totalB)
        cout << "Road A is busier.\n";
    else if (totalB > totalA)
        cout << "Road B is busier.\n";
    else
        cout << "Both roads have equal traffic.\n";

    // Congestion detection
    cout << "\nRoad A:";
    detectCongestion(roadA, SIZE);

    cout << "\nRoad B:";
    detectCongestion(roadB, SIZE);

    return 0;
}

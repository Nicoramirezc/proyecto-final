/**
 * @file tests/test_main.cpp
 * @brief Tests unitarios con GoogleTest para Bus Escape.
 * @note Requiere: sudo apt install libgtest-dev cmake
 *       Luego compilar con: make google-test
 */
#include <gtest/gtest.h>
#include "Board.h"
#include "Bus.h"
#include "Car.h"
#include "Passenger.h"
#include "PassengerQueue.h"
#include "ParkingZone.h"
#include "LevelLoader.h"

using namespace std;

// ==================== Vehiculos / Tablero ====================

TEST(BoardTest, NoCollisionWhenEmpty) {
    Board board(6, 6);
    EXPECT_FALSE(board.hasCollision(0, 0, 3, HORIZONTAL, -1));
}

TEST(BoardTest, DetectsCollision) {
    Board board(6, 6);
    auto bus = make_shared<Bus>(1, 0, 0, 3, "ROJO", HORIZONTAL);
    auto car = make_shared<Car>(2, 2, 0, 2, "AZUL", VERTICAL);
    board.addVehicle(bus);
    board.addVehicle(car);
    EXPECT_TRUE(board.hasCollision(0, 0, 3, HORIZONTAL, -1));
}

TEST(BoardTest, VehicleMovesCorrectly) {
    Board board(6, 6);
    auto bus = make_shared<Bus>(1, 0, 0, 3, "ROJO", HORIZONTAL);
    board.addVehicle(bus);
    EXPECT_TRUE(board.canVehicleMove(1, 1, 0));
    EXPECT_FALSE(board.canVehicleMove(1, 4, 0));
    board.moveVehicle(1, 1, 0);
    EXPECT_EQ(bus->getX(), 1);
}

TEST(VehicleTest, PolymorphismType) {
    shared_ptr<Vehicle> v1 = make_shared<Bus>(1, 0, 0, 3, "ROJO", HORIZONTAL);
    shared_ptr<Vehicle> v2 = make_shared<Car>(2, 0, 0, 2, "AZUL", VERTICAL);
    EXPECT_EQ(v1->getType(), "Bus");
    EXPECT_EQ(v2->getType(), "Car");
    EXPECT_EQ(v1->getMaxCapacity(), 3);
    EXPECT_EQ(v2->getMaxCapacity(), 2);
}

TEST(VehicleTest, PassengerManagement) {
    auto bus = make_shared<Bus>(1, 0, 0, 3, "ROJO", HORIZONTAL);
    EXPECT_EQ(bus->getPassengerCount(), 0);
    bus->addPassenger();
    EXPECT_EQ(bus->getPassengerCount(), 1);
    EXPECT_FALSE(bus->isFull());
    bus->addPassenger();
    bus->addPassenger();
    EXPECT_TRUE(bus->isFull());
}

// ==================== Pasajeros / Cola ====================

TEST(PassengerQueueTest, FIFOOrder) {
    PassengerQueue q;
    q.addPassenger(Passenger(1, "ROJO"));
    q.addPassenger(Passenger(2, "AZUL"));
    EXPECT_EQ(q.getSize(), 2);
    EXPECT_EQ(q.frontPassenger().getColor(), "ROJO");
    q.removePassenger();
    EXPECT_EQ(q.frontPassenger().getColor(), "AZUL");
    EXPECT_EQ(q.getSize(), 1);
}

TEST(PassengerQueueTest, EmptyQueue) {
    PassengerQueue q;
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.frontPassenger().getId(), -1);
}

// ==================== Zonas de Parqueo ====================

TEST(ParkingZoneTest, ParkAndRemove) {
    ParkingZone z(1);
    auto car = make_shared<Car>(1, 0, 0, 2, "VERDE", HORIZONTAL);
    EXPECT_TRUE(z.parkVehicle(car));
    EXPECT_TRUE(z.getIsOccupied());
    EXPECT_EQ(z.getVehicle()->getId(), 1);
    z.removeVehicle();
    EXPECT_FALSE(z.getIsOccupied());
    EXPECT_EQ(z.getVehicle(), nullptr);
}

TEST(ParkingZoneTest, DoubleParkFails) {
    ParkingZone z(1);
    auto car1 = make_shared<Car>(1, 0, 0, 2, "VERDE", HORIZONTAL);
    auto car2 = make_shared<Car>(2, 0, 0, 2, "AZUL", HORIZONTAL);
    EXPECT_TRUE(z.parkVehicle(car1));
    EXPECT_FALSE(z.parkVehicle(car2));
}

// ==================== LevelLoader ====================

TEST(LevelLoaderTest, LoadValidLevel) {
    LevelData data;
    bool ok = LevelLoader::load("levels/nivel1.txt", data);
    EXPECT_TRUE(ok);
    EXPECT_GT(data.width, 0);
    EXPECT_GT(data.height, 0);
    EXPECT_FALSE(data.vehicles.empty());
    EXPECT_FALSE(data.passengers.empty());
}

TEST(LevelLoaderTest, LoadInvalidLevel) {
    LevelData data;
    bool ok = LevelLoader::load("levels/no_existe.txt", data);
    EXPECT_FALSE(ok);
}

// ==================== Main ====================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

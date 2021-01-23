#include "Bank.h"
#include "../googletest/googletest/include/gtest/gtest.h"

int Customer::Counter = 0;

namespace {
    Bank bank;
    //Registration
    TEST(BankTest, Registration)
    {
        bool is_registered = false;
        is_registered = bank.Registration("test","test");
        EXPECT_TRUE(is_registered);
    }
    //Wrong Registration
    TEST(BankTest, WrongRegistration)
    {
        bool is_wrongReg = false;
        is_wrongReg = !(bank.Registration("test","test"));
        EXPECT_TRUE(is_wrongReg);
    }
    
    //login
    TEST(BankTest, Login)
    {
        bool is_logined = false;
        is_logined = bank.LogIn("test","test");
        EXPECT_TRUE(is_logined);
    }

    //Check account information
    TEST(BankTest, CheckInformation)
    {
        EXPECT_EQ("test",bank.GetPersonName());
        //For all users start balance equals 300000
        EXPECT_EQ(300000, bank.GetPersonBalance());
    }

    //Deposit
    TEST(BankTest, Deposit)
    {
        bool is_deposited = false;
        is_deposited = bank.Deposit("20000");
        EXPECT_TRUE(is_deposited);
        bank.RemoveAccount();
    }

}//namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


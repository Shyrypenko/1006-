#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <locale>

class Account {
private:
    std::string ownerSurname;
    int accountNumber;
    double interestRate;
    double balance;       

public:
    Account(const std::string& surname, int number, double rate, double initialBalance)
        : ownerSurname(surname), accountNumber(number), interestRate(rate), balance(initialBalance) {}

    void changeOwner(const std::string& newSurname) {
        ownerSurname = newSurname;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            std::cerr << "Недостаточно средств на счете." << std::endl;
            return false;
        }
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void applyInterest() {
        balance += balance * (interestRate / 100);
    }

    double toDollars(double exchangeRate = 95.0) const {
        return balance / exchangeRate;
    }

    double toEuros(double exchangeRate = 105.0) const {
        return balance / exchangeRate;
    }
    std::string numberToWords() const {
        static const std::string ones[] = { "", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять" };
        static const std::string teens[] = { "", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать" };
        static const std::string tens[] = { "", "десять", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
        static const std::string hundreds[] = { "", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };

        int amount = static_cast<int>(balance);
        std::ostringstream words;

        if (amount >= 100) {
            words << hundreds[amount / 100] << " ";
            amount %= 100;
        }

        if (amount >= 20) {
            words << tens[amount / 10] << " ";
            amount %= 10;
        }
        else if (amount >= 11) {
            words << teens[amount % 10] << " ";
            amount = 0;
        }
        else if (amount == 10) {
            words << tens[1] << " ";
            amount = 0;
        }

        words << ones[amount];

        return words.str();
    }

    void printAccountInfo() const {
        std::cout << "Владелец: " << ownerSurname << std::endl;
        std::cout << "Номер счета: " << accountNumber << std::endl;
        std::cout << "Процент начисления: " << interestRate << "%" << std::endl;
        std::cout << "Сумма на счете: " << std::fixed << std::setprecision(2) << balance << " руб." << std::endl;
        std::cout << "Сумма на счете прописью: " << numberToWords() << std::endl;
    }
};

int main() {
    Account acc("Иванов", 123456, 5.0, 1000.0);

    acc.printAccountInfo();

    acc.deposit(500.0);
    std::cout << "\nПосле пополнения на 500 руб:" << std::endl;
    acc.printAccountInfo();

    acc.withdraw(300.0);
    std::cout << "\nПосле снятия 300 руб:" << std::endl;
    acc.printAccountInfo();

    acc.applyInterest();
    std::cout << "\nПосле начисления процентов:" << std::endl;
    acc.printAccountInfo();

    std::cout << "\nЕдоллары: " << acc.toDollars() << " USD" << std::endl;
    std::cout << "Евро: " << acc.toEuros() << " EUR" << std::endl;
}

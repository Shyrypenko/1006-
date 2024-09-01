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
            std::cerr << "������������ ������� �� �����." << std::endl;
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
        static const std::string ones[] = { "", "����", "���", "���", "������", "����", "�����", "����", "������", "������" };
        static const std::string teens[] = { "", "�����������", "����������", "����������", "������������", "����������", "�����������", "����������", "������������", "������������" };
        static const std::string tens[] = { "", "������", "��������", "��������", "�����", "���������", "����������", "���������", "�����������", "���������" };
        static const std::string hundreds[] = { "", "���", "������", "������", "���������", "�������", "��������", "�������", "���������", "���������" };

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
        std::cout << "��������: " << ownerSurname << std::endl;
        std::cout << "����� �����: " << accountNumber << std::endl;
        std::cout << "������� ����������: " << interestRate << "%" << std::endl;
        std::cout << "����� �� �����: " << std::fixed << std::setprecision(2) << balance << " ���." << std::endl;
        std::cout << "����� �� ����� ��������: " << numberToWords() << std::endl;
    }
};

int main() {
    Account acc("������", 123456, 5.0, 1000.0);

    acc.printAccountInfo();

    acc.deposit(500.0);
    std::cout << "\n����� ���������� �� 500 ���:" << std::endl;
    acc.printAccountInfo();

    acc.withdraw(300.0);
    std::cout << "\n����� ������ 300 ���:" << std::endl;
    acc.printAccountInfo();

    acc.applyInterest();
    std::cout << "\n����� ���������� ���������:" << std::endl;
    acc.printAccountInfo();

    std::cout << "\n��������: " << acc.toDollars() << " USD" << std::endl;
    std::cout << "����: " << acc.toEuros() << " EUR" << std::endl;
}

#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include<map>
#include<set>
class Automaton
{
private:
	std::vector<char> multimeStari;
	std::vector<char> alfabet;
	char stareInitiala;
	std::vector<char> stariFinale;
	std::multimap<std::pair<char, std::string>, char > tranzitii;

public:
	Automaton() = default;
	void SetMultimeStari(std::vector<char> multime);
	void SetStariFinale(std::vector<char> multime);
	void SetAlfabet(std::vector<char> multime);
	void SetTranzitii(const std::multimap<std::pair<char, std::string>, char>& tranzitii);
	void SetStareInitiala(char symbol);
	void AddNewTransition(char firstState, std::string letter, char secondState);
	void AddNewState(char state);
	std::vector<char> GetMultimeStari();
	std::vector<char> GetStariFinale();
	std::vector<char> GetAlfabet();
	std::multimap<std::pair<char, std::string>, char> GetTranzitii();
	char GetStareInitiala();
	friend std::istream& operator>>(std::istream& fisierIntrare, Automaton& automat);
	friend std::ostream& operator<<(std::ostream& fisierIesire, Automaton& automat);

};


#include "Automaton.h"

void Automaton::SetMultimeStari(std::vector<char> multime)
{
    for (int i : multime)
    {
        multimeStari.push_back(i);
    }
}

void Automaton::SetStariFinale(std::vector<char> multime)
{
    for (int i : multime)
    {
        stariFinale.push_back(i);
    }
}

void Automaton::SetAlfabet(std::vector<char> multime)
{
    for (char i : multime)
    {
        alfabet.push_back(i);
    }
}

void Automaton::SetTranzitii(const std::multimap<std::pair<char, std::string>, char>& tranzitii)
{
    this->tranzitii = tranzitii;
}

void Automaton::SetStareInitiala(char symbol)
{
    stareInitiala = symbol;
}

void Automaton::AddNewTransition(char firstState, std::string sequence, char secondState)
{
    tranzitii.insert(std::make_pair(std::make_pair(firstState, sequence), secondState));
}

void Automaton::AddNewState(char state)
{
    multimeStari.push_back(state);
}

std::vector<char> Automaton::GetMultimeStari()
{
    return multimeStari;
}

std::vector<char> Automaton::GetStariFinale()
{
    return stariFinale;
}

std::vector<char> Automaton::GetAlfabet()
{
    return alfabet;
}

std::multimap<std::pair<char, std::string>, char> Automaton::GetTranzitii()
{
    return tranzitii;
}

char Automaton::GetStareInitiala()
{
    return stareInitiala;
}

std::istream& operator>>(std::istream& fisierIntrare, Automaton& automat)
{
    std::string text;
    char stare1, stare2;
    char simbol;

    std::getline(fisierIntrare, text, '\n');
    for (int index = 0; index < text.length(); index++)
        if (text[index] != ' ')
        {
            automat.multimeStari.push_back(text[index]);
        }
    std::getline(fisierIntrare, text, '\n');
    for (int index = 0; index < text.length(); index++)
        if (text[index] != ' ')
            automat.alfabet.push_back(text[index]);
    std::getline(fisierIntrare, text, '\n');
    for (int index = 0; index < text.length(); index++)
        if (text[index] != ' ')
        {
            automat.stariFinale.push_back(text[index]);
        }
    fisierIntrare >> automat.stareInitiala;

    while (fisierIntrare >> stare1 >> simbol >> stare2)
    {
        automat.tranzitii.insert(std::make_pair(std::make_pair(stare1, std::string(1, simbol)), stare2));
    }
    return fisierIntrare;
}

std::ostream& operator<<(std::ostream& fisierIesire, Automaton& automat)
{
    fisierIesire << "Starile: ";
    for (int index = 0; index < automat.GetMultimeStari().size(); index++)
    {
        fisierIesire << automat.GetMultimeStari()[index] << " ";
    }
    fisierIesire << "\nAlfabet: ";
    for (int index = 0; index < automat.GetAlfabet().size(); index++)
    {
        fisierIesire << automat.GetAlfabet()[index] << " ";
    }
    fisierIesire << "\nStari finale: ";
    for (int index = 0; index < automat.GetStariFinale().size(); index++)
    {
        fisierIesire << automat.GetStariFinale()[index] << " ";
    }
    fisierIesire << "\nStare initiala: " << automat.GetStareInitiala();
    fisierIesire << "\nTranzitii:\n";
    for (auto it : automat.GetTranzitii())
    {
        fisierIesire << it.first.first << " " << it.first.second << " " << it.second << "\n";
    }

    return fisierIesire;
}

#include <iostream>
#include "Automaton.h"

#include <unordered_map>
#include <unordered_set>

Automaton GNFA(Automaton& automaton)
{
	char finalState = 'F';
	char startState = 'S';
	automaton.AddNewTransition(startState, "&", automaton.GetStareInitiala());
	for (auto state : automaton.GetStariFinale())
	{
		automaton.AddNewTransition(state, "&", finalState);
	}
	automaton.AddNewState(startState);
	automaton.AddNewState(finalState);

	return automaton;
}

void RegularExpression(Automaton automaton)
{
	automaton = GNFA(automaton);
	std::multimap<std::pair<char, std::string>, char> transition = automaton.GetTranzitii();
	std::unordered_map<char, std::unordered_map<char, std::string>> transitions;
	std::string expression1, expression2, expression3, expression4, newExpression;
	std::vector<char> stari = automaton.GetMultimeStari();
	std::unordered_map<char, std::unordered_set<char>>predecessors;
	std::unordered_map<char, std::unordered_set<char>>successors;
	for (auto it = transition.begin(); it != transition.end(); it++)
	{
		if (transitions[(*it).first.first][(*it).second] == "")
			transitions[(*it).first.first][(*it).second] = (*it).first.second;
		else
			transitions[(*it).first.first][(*it).second] += "+" + (*it).first.second;

	}
	for (auto it = transition.begin(); it != transition.end(); it++)
	{
		predecessors[(*it).second].insert((*it).first.first);
		successors[(*it).first.first].insert((*it).second);
	}

	while (stari.size() > 2)
	{
		for (auto predecessor : predecessors[stari[0]])
		{
			if (predecessor != stari[0])
				for (auto successor : successors[stari[0]])
				{
					if (successor != stari[0])
					{
						expression1 = "", expression2 = "", expression3 = "", expression4 = "", newExpression = "";
						if (transitions[predecessor][successor] != "")
							expression4 = transitions[predecessor][successor];
						else
							if (transitions[predecessor][stari[0]] == "&" && transitions[stari[0]][successor] == "&")
								expression4 = "&";
						if (transitions[stari[0]][stari[0]] != "" && transitions[stari[0]][stari[0]] != "&")
							expression2 = transitions[stari[0]][stari[0]] + "*";
						if (transitions[predecessor][stari[0]] != "" && transitions[predecessor][stari[0]] != "&")
							expression1 = transitions[predecessor][stari[0]];
						if (transitions[stari[0]][successor] != "" && transitions[stari[0]][successor] != "&")
							expression3 = transitions[stari[0]][successor];
						newExpression = expression1 + expression2 + expression3;
						if (expression4 != "" && newExpression != "")
							newExpression += ("+" + expression4);
						else
							if (expression4 == "&")
								newExpression += expression4;
						transitions[predecessor][successor] = "(" + newExpression + ")";
					}
				}
		}
		transitions.erase(stari[0]);
		for (auto it = transitions.begin(); it != transitions.end();)
			if ((*it).second.find(stari[0]) != (*it).second.end())
				(*it).second.erase(stari[0]);
			else
				it++;
		predecessors.clear();
		successors.clear();
		for (auto it = transitions.begin(); it != transitions.end(); it++)
		{
			for (auto it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++)
			{
				successors[(*it).first].insert((*it1).first);
				predecessors[(*it1).first].insert((*it).first);
			}
		}

		stari.erase(stari.begin());

	}
	std::cout << transitions['S']['F'];

}



int main()
{
	Automaton automaton;
	std::ifstream fisierIntrare("automaton.in");
	std::ofstream fisierIesire("automaton.out");
	fisierIntrare >> automaton;
	fisierIesire << automaton;
	RegularExpression(automaton);
	fisierIesire << automaton;
	fisierIntrare.close();
	fisierIesire.close();
	return 0;
}


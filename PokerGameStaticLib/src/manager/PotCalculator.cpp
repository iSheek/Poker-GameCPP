/**
 * @file PotCalculator.cpp
 * @brief File containing definition of PotCalculator namespace's functions
 */

#include "PotCalculator.h"
#include "PublicPlayerInfo.h"
#include <vector>
#include <algorithm>
#include <stdexcept>


namespace PotCalculator
{
	namespace
	{
		/**
		 * @brief Function that returns the biggest current contribution
		 * @param playersContribution vector of every player's contribution to pots
		 * @return max contribution
		 */
		int maxAllChips(const std::vector<int>& playersContribution)
		{
			int max{};

			for (int i{}; i < playersContribution.size(); ++i)
			{
				if (max < playersContribution[i])
				{
					max = playersContribution[i];
				}
			}

			return max;
		}

		/**
		 * @brief Function that returns the smallest current contribution of non folded player
		 * @param playersContribution vector of every player's contribution to pots
		 * @param publicPlayersInfo vector of public informations of every player
		 * @return min contribution of nonfolded players
		 */
		int minNonFoldedChips(const std::vector<int>& playersContribution, const std::vector<PublicPlayerInfo>& publicPlayersInfo)
		{
			int min{ maxAllChips(playersContribution) };

			for (int i{}; i < playersContribution.size(); ++i)
			{
				if (playersContribution[i] <= 0) continue;
				if (!publicPlayersInfo[i].hasFolded && min > playersContribution[i])
				{
					min = playersContribution[i];
				}
			}

			return min;
		}

	}

	std::vector<Pot> getAllPots(const std::vector<PublicPlayerInfo>& publicPlayersInfo)
	{
		if (publicPlayersInfo.size() == 0)
		{
			throw std::runtime_error("ERROR! NO PLAYERS IN PUBLICPLAYERSINFO VECTOR");
		}

		std::vector<int> playersContribution{};
		std::vector<Pot> pots{};

		int maxChips{};
		int minChips{ (*std::max_element(publicPlayersInfo.begin(), publicPlayersInfo.end(), [](const PublicPlayerInfo& a, const PublicPlayerInfo& b) {return a.totalBet < b.totalBet; })).totalBet };
		for (const auto& p : publicPlayersInfo)
		{
			playersContribution.push_back(p.totalBet);
			minChips = minChips > p.totalBet && !p.hasFolded && p.totalBet > 0 ? p.totalBet : minChips;
			maxChips = maxChips < p.totalBet ? p.totalBet : maxChips;
		}

		while (maxChips > 0)
		{

			Pot pot{};

			for (int i{}; i < playersContribution.size(); ++i)
			{
				if (playersContribution[i] <= 0)
				{
					continue;
				}

				if (!publicPlayersInfo[i].hasFolded)
				{
					pot.authorizedPlayersIndices.push_back(i);
				}

				if (playersContribution[i] < minChips)
				{
					pot.totalChips += playersContribution[i];
					playersContribution[i] = 0;
				}
				else
				{
					pot.totalChips += minChips;
					playersContribution[i] -= minChips;
				}



			}

			minChips = minNonFoldedChips(playersContribution, publicPlayersInfo);
			maxChips = maxAllChips(playersContribution);

			pots.push_back(pot);
		}

		if (pots.size() > 1 && pots[pots.size() - 1].authorizedPlayersIndices.empty())
		{
			pots[pots.size() - 2].totalChips += pots[pots.size() - 1].totalChips;
			pots.pop_back();
		}


		return pots;
	}

}
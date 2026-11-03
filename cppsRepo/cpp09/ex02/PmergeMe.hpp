#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <vector>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;

	template <typename IdxCont, typename ValCont>
	static void	fordJohnson(IdxCont& idx, const ValCont& values);

	template <typename IdxCont, typename ValCont>
	static void	sortByIndex(ValCont& values);

public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void	loadVector(int argc, char** argv);
	void	loadDeque(int argc, char** argv);
	void	sortVector();
	void	sortDeque();

	const std::vector<int>&	getVector() const;
	const std::deque<int>&	getDeque() const;
};

template <typename IdxCont, typename ValCont>
void PmergeMe::fordJohnson(IdxCont& idx, const ValCont& values)
{
	size_t n = idx.size();
	if (n < 2)
		return;

	IdxCont bigs;
	IdxCont partner(values.size());
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		size_t a = idx[i];
		size_t b = idx[i + 1];
		if (values[a] < values[b])
		{
			size_t tmp = a;
			a = b;
			b = tmp;
		}
		bigs.push_back(a);
		partner[a] = b;
	}
	bool hasStraggler = (n % 2 == 1);
	size_t straggler = hasStraggler ? idx[n - 1] : 0;

	fordJohnson(bigs, values);

	IdxCont chain;
	chain.push_back(partner[bigs[0]]);
	chain.insert(chain.end(), bigs.begin(), bigs.end());

	size_t pairCount = bigs.size();
	size_t smallCount = hasStraggler ? pairCount + 1 : pairCount;
	size_t prev = 1;
	size_t curr = 3;
	while (prev < smallCount)
	{
		size_t start = (curr < smallCount) ? curr : smallCount;
		for (size_t i = start; i > prev; --i)
		{
			size_t b;
			size_t hi = 0;
			if (i == pairCount + 1)
			{
				b = straggler;
				hi = chain.size();
			}
			else
			{
				size_t a = bigs[i - 1];
				b = partner[a];
				while (chain[hi] != a)
					++hi;
			}
			size_t lo = 0;
			while (lo < hi)
			{
				size_t mid = lo + (hi - lo) / 2;
				if (values[b] < values[chain[mid]])
					hi = mid;
				else
					lo = mid + 1;
			}
			chain.insert(chain.begin() + lo, b);
		}
		size_t next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	idx = chain;
}

template <typename IdxCont, typename ValCont>
void PmergeMe::sortByIndex(ValCont& values)
{
	IdxCont idx;
	for (size_t i = 0; i < values.size(); ++i)
		idx.push_back(i);
	fordJohnson(idx, values);

	ValCont sorted;
	for (size_t i = 0; i < idx.size(); ++i)
		sorted.push_back(values[idx[i]]);
	values = sorted;
}

#endif

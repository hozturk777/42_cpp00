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

// idx: values icindeki indeksler. Ford-Johnson ile values degerlerine gore siralar.
// Degerler yerine indeks siralanir; boylece tekrar eden sayilarda bile
// her kucuk eleman (b) kendi buyugune (a) bagli kalir.
// IdxCont / ValCont: std::vector ya da std::deque ([] ve insert yeterli).
template <typename IdxCont, typename ValCont>
void PmergeMe::fordJohnson(IdxCont& idx, const ValCont& values)
{
	size_t n = idx.size();
	if (n < 2)
		return;

	// 1) Ikiserli esle: buyuk -> bigs, kucuk -> partner[buyuk]
	IdxCont bigs;
	IdxCont partner(values.size());
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		size_t a = idx[i]; // 0
		size_t b = idx[i + 1]; // 1
		if (values[a] < values[b]) //values[0] < values[1]
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

	// 2) Buyukleri ayni algoritmayla sirala
	fordJohnson(bigs, values);

	// 3) Ana zincir: b1 en basa (b1 < a1 <= digerleri), sonra a1..ak
	IdxCont chain;
	chain.push_back(partner[bigs[0]]);
	chain.insert(chain.end(), bigs.begin(), bigs.end());

	// 4) b2..b(smallCount)'u Jacobsthal sirasiyla ekle: (3,2) (5,4) (11..6) (21..12) ...
	// Tek kalan eleman varsa b(pairCount+1) olarak siraya dahildir; a'si olmadigi
	// icin tum zincirde aranir.
	size_t pairCount = bigs.size(); // 1
	size_t smallCount = hasStraggler ? pairCount + 1 : pairCount; // 2
	size_t prev = 1;
	size_t curr = 3;
	while (prev < smallCount)
	{
		size_t start = (curr < smallCount) ? curr : smallCount; // 3
		for (size_t i = start; i > prev; --i)
		{
			size_t b;
			size_t hi = 0;
			if (i == pairCount + 1)
			{
				b = straggler; // [4] = 6
				hi = chain.size(); // 2
			}
			else
			{
				// b < a oldugu icin yalnizca a'nin solunda aranir
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

// values'u Ford-Johnson ile siralar; indeksler IdxCont icinde tutulur
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

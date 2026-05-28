#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void eraseByIndices(
	std::vector<T>& vec,
	std::vector<size_t> indices
)
{
	std::sort(indices.begin(), indices.end());
	indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

	for (auto it = indices.rbegin(); it != indices.rend(); ++it)
	{
		vec.erase(vec.begin() + *it);
	}
}

// 如果 vector 元素很大的话，考虑rebuid
template <typename T>
void rebuid(std::vector<T>& vec, std::vector<size_t> indices)
{
	std::sort(indices.begin(), indices.end());
	indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

	std::vector<T> res;
	res.reserve(vec.size());
	size_t idx = 0;
	for (auto i = 0; i < vec.size(); ++i)
	{
		if (idx < indices.size() && i == indices[idx])
		{
			++idx;
			continue;
		}
		res.emplace_back(vec[i]);
	}
	vec.swap(res);
}

int main()
{
	std::vector<int> vec = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

	auto v = vec;
	eraseByIndices(vec, { 1, 3, 4 });
	rebuid(v, { 1, 3, 4 });
	for (const auto& item : vec)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;

	std::cout << "========================================================" << std::endl;

	for (const auto& item : v)
	{
		std::cout << item << " ";
	}
	std::cout << std::endl;
}
#include <vector>
#include <utility>

using namespace std;


template <typename T>
pair<T, T> hist(vector<T> &h)
{
	int n = h.size();
	pair<T, T> answer;
	T s = 0;
	
	vector<int> st;
	h.push_back(0);
	for (int i = 0; i <= n; ++i) {
		while (!st.empty() && h[st.back()] >= h[i]) {
			int ceiling = st.back();
			st.pop_back();
			T width = (st.empty() ? i : i - st.back() - 1);
			T ss = h[ceiling] * width;
			if (ss > s) {
				s = ss;
				answer = {h[ceiling], width};
			}
		}
		st.push_back(i);
	}
	h.pop_back();
	return answer;
}


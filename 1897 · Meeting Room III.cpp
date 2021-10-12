//https://www.lintcode.com/problem/1897/description
class Solution {
public:
    struct segtree
    {
        int size;
        vector<int> values;
        void init(int n)
        {
            size = 1;
            while (size < n)size *= 2;
            values.assign(2 * size, 0);
        }
        void build(vector<int>&a, int x, int lx, int rx)
        {
            if (rx - lx == 1)
            {
                if (lx < (int)a.size())
                {
                    values[x] = a[lx];
                }
                return;
            }
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            values[x] = max(values[2 * x + 1] , values[2 * x + 2]);
        }
        void build(vector<int> &a)
        {
            build(a, 0, 0, size);
        }
        void set(int i, int v, int x, int lx, int rx)
        {
            if (rx - lx == 1)
            {
                values[x] = v;
                return;
            }
            int m = (lx + rx) / 2;
            if (i < m)
            {
                set(i, v, 2 * x + 1, lx, m);
            }
            else
            {
                set(i, v, 2 * x + 2, m, rx);
            }
            values[x] = max(values[2 * x + 1] , values[2 * x + 2]);
        }
        void set(int i, int v)
        {
            set(i, v, 0, 0, size);
        }
        int calc(int l, int r, int x, int lx, int rx)
        {
            if (lx >= r or l >= rx) return INT_MIN;
            if (lx >= l and rx <= r) return values[x];
            int m = (lx + rx) / 2;
            int s1 = calc(l, r, 2 * x + 1, lx, m);
            int s2 = calc(l, r, 2 * x + 2, m, rx);
            return max(s1 , s2);
        }
        int calc(int l, int r)
        {
            return calc(l, r, 0, 0, size);
        }
    };
    vector<bool> meetingRoomIII(vector<vector<int>>&a, int rooms, vector<vector<int>>&ask) {
        vector<int>cur(50005);
        for (int i = 0; i < a.size(); ++i) {
            cur[a[i][1] - 1] += 1;
            cur[a[i][0] - 1] -= 1;
        }
        for (int i = 50001; i >= 0; --i) {
            cur[i] += cur[i + 1];
        }
        segtree st;
        st.init(cur.size());
        st.build(cur);
        vector<bool>ans;
        for (int i = 0; i < ask.size(); ++i) {
            int maxx = st.calc(ask[i][0], ask[i][1]);
            cout << maxx << " ";
            if (maxx < rooms) {
                ans.push_back(true);
            }
            else {
                ans.push_back(false);
            }
        }
        return ans;

    }
};

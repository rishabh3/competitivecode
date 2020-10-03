from functools import reduce


def get_min_cost(d, m_element):
    res = 0
    temp = d[m_element]
    swp_cnt = abs(temp[0] - temp[1])//2;
    if swp_cnt != 0:
        val = (temp[0] + temp[1])//2;
        d[m_element] = [val]*2
    a = []
    b = []
    for i in d:
        if i != m_element:
            if swp_cnt != 0:
                if temp[0] > temp[1]:
                    while(swp_cnt != 0 and d[i][0] < d[i][1]):
                        d[i][0] += 1
                        d[i][1] -= 1
                        swp_cnt -= 1
                        res += m_element
                else:
                    while(swp_cnt != 0 and d[i][1] < d[i][0]):
                        d[i][1] += 1
                        d[i][0] -= 1
                        swp_cnt -= 1
                        res += m_element
            else:
                times = abs(d[i][0] - d[i][1]) // 2
                if d[i][0] > d[i][1]:
                    a.extend([i]*times)
                elif d[i][0] < d[i][1]:
                    b.extend([i]*times)
    for i in range(len(a)):
        res += min(2*m_element, min(a[i], b[len(a) - 1 - i]))
    return res

test = int(input().strip())
for i in range(test):
    n = int(input().strip())
    a = list(map(int, input().strip().split(' ')))
    xor_elem = reduce(lambda x,y: x^y, a)
    b = list(map(int, input().strip().split(' ')))
    xor_elem ^= reduce(lambda x,y: x^y, b)
    d = {}
    for j in a:
        try:
            d[j][0] += 1
        except KeyError:
            d[j] = [1, 0]
    for j in b:
        try:
            d[j][1] += 1
        except KeyError:
            d[j] = [0, 1]
    if xor_elem == 0:
        res = get_min_cost(d, min(min(a), min(b)))
    else:
        res = -1
    print(res)

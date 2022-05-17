#include <bits/stdc++.h>
using namespace std;
int seg[1000][1000] = { 0 }; //base node
int fseg[1000][1000] = { 0 }; //final segment tree
int arr[4][4] = {
{ 1, 2, 31, 4 },
{ 8, 6, 18, 3 },
{ 1, 19, 5, 9 },
{ 4, 0, 6, 12 },
};
int size = 4;//size of the x-coordinate
int init_segment(int low, int high, int pos, int strip) //construction of segment tree
{
if (high == low) {
seg[strip][pos] = arr[strip][low];
}
else {
int mid = (low + high) / 2;
init_segment(low, mid, 2 * pos, strip);
init_segment(mid + 1, high, 2 * pos + 1, strip);
seg[strip][pos] = seg[strip][2 * pos] + seg[strip][2 * pos + 1];
}
}
int fin_segment(int low, int high, int pos) //segment tree final construction
{
if (high == low) {
for (int i = 1; i < 2 * size; i++)
fseg[pos][i] = seg[low][i];
}
else {
int mid = (low + high) / 2;
fin_segment(low, mid, 2 * pos);
fin_segment(mid + 1, high, 2 * pos + 1);
for (int i = 1; i < 2 * size; i++)
fseg[pos][i] = fseg[2 * pos][i] + fseg[2 * pos + 1][i];
}
}
int final_query(int pos, int start, int end, int x1, int x2, int node)//sum query function
{
if (x2 < start || end < x1) {
return 0;
}
if (x1 <= start && end <= x2) {
return fseg[node][pos];
}
int mid = (start + end) / 2;
int p1 = final_query(2 * pos, start, mid, x1, x2, node);
int p2 = final_query(2 * pos + 1, mid + 1, end, x1, x2, node);
return (p1 + p2);
}
int check_query(int pos, int start, int end, int y1, int y2, int x1, int x2)
{
if (y2 < start || end < y1) {
return 0;
}
if (y1 <= start && end <= y2) {
return (final_query(1, 1, 4, x1, x2, pos));
}
int mid = (start + end) / 2;
int p1 = check_query(2 * pos, start, mid, y1, y2, x1, x2);
int p2 = check_query(2 * pos + 1, mid + 1,end, y1, y2, x1, x2);
return (p1 + p2);
}
int final_update(int pos, int low, int high, int x, int val, int node)
{
if (low == high) {
fseg[node][pos] = val;
}
else {
int mid = (low + high) / 2;
if (low <= x && x <= mid) {
final_update(2 * pos, low, mid, x, val, node);
}
else {
final_update(2 * pos + 1, mid + 1, high, x, val, node);
}
fseg[node][pos] = fseg[node][2 * pos] + fseg[node][2 * pos + 1];
}
}
int update(int pos, int low, int high, int x, int y, int val)
{
if (low == high) {
final_update(1, 1, 4, x, val, pos);
}
else {
int mid = (low + high) / 2;
if (low <= y && y <= mid) {
update(2 * pos, low, mid, x, y, val);
}
else {
update(2 * pos + 1, mid + 1, high, x, y, val);
}
for (int i = 1; i < size; i++)
fseg[pos][i] = fseg[2 * pos][i] + fseg[2 * pos + 1][i];
}
}
int main()
{
int pos = 1;
int low = 0;
int high = 3;
for (int strip = 0; strip < 4; strip++)
init_segment(low, high, 1, strip);
fin_segment(low, high, 1);
cout << "The sum of the submatrix (y1, y2)->(2, 3), " << " (x1, x2)->(2, 3) is " << query(1, 1,
4, 2, 3, 2, 3) << endl;
update(1, 1, 4, 2, 3, 150);
cout << "The sum of the submatrix (y1, y2)->(2, 3) after updating the value, " << "(x1,
x2)->(2, 3) is " << query(1, 1, 4, 2, 3, 2, 3) << endl;
return 0;
}

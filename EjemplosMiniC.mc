int x = 0;
int y;
for (int i = 0, j = 2; i < j; i++, --j) {
  if (i == 1) cout << "ok" << i;
  else x += i;
}
x = x + 3;
while (x > 0) { x--; }
cin >> x >> y;
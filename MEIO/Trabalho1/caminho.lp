/* Função objetivo */
min: 3 xab + 3 xbc + 3 xbe + 4 xcd + 2 xdi + 12 xdm + 6 xek + 2 xfe + 2 xfg + 4 xgc + 3 xgh + 4 xgn + 2 xhj + 3 xih + 5 xji + 3 xjm + 4 xkf + 2 xkl + 10 xla + 4 xmn + 4 xnl;

/* Restrições de não negatividade */
xab >= 1;
xbc >= 1;
xbe >= 1;
xcd >= 1;
xdi >= 1;
xdm >= 1;
xek >= 1;
xfe >= 1;
xfg >= 1;
xgc >= 1;
xgh >= 1;
xgn >= 1;
xhj >= 1;
xih >= 1;
xji >= 1;
xjm >= 1;
xkf >= 1;
xkl >= 1;
xla >= 1;
xmn >= 1;
xnl >= 1;

/* Outras restrições */
xab - xla = 0;
xbc + xbe - xab = 0;
xbe + xfe - xek = 0;
xbc + xgc - xcd = 0;
xdm + xdi - xcd = 0;
xdi + xji - xih = 0;
xfe + xfg - xkf = 0;
xgc + xgh + xgn - xfg = 0;
xih + xgh - xhj = 0;
xjm + xji - xhj = 0;
xdm + xjm - xmn = 0;
xkf + xkl - xek = 0;
xkl + xnl - xla = 0;
xgn + xmn - xnl = 0;

/* Restrição de integralidade */
int xab, xbc, xbe, xcd, xdi, xdm, xek, xfe, xfg, xgc, xgh, xgn, xhj, xih, xji, xjm, xkf, xkl, xla, xmn, xnl;
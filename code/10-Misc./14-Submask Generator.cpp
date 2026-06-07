int mask = 0; // any value
for (int submask = mask; submask; submask = (submask - 1) & mask) {}
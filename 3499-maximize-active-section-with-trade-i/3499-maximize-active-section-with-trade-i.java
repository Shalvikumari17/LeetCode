class Solution {
    public int maxActiveSectionsAfterTrade(String s) {
        int ones = 0;

        for (char c : s.toCharArray()) {
            if (c == '1') {
                ones++;
            }
        }

        String t = "1" + s + "1";

        int prevZero = 0;
        int maxGain = 0;
        int i = 0;

        while (i < t.length()) {
            int count = 0;
            char c = t.charAt(i);

            while (i < t.length() && t.charAt(i) == c) {
                count++;
                i++;
            }

            if (c == '0') {
                prevZero = count;
            } else {
                // Current 1-block is followed by a 0-block
                if (i < t.length() && prevZero > 0) {
                    int j = i;
                    int nextZero = 0;

                    while (j < t.length() && t.charAt(j) == '0') {
                        nextZero++;
                        j++;
                    }

                    if (nextZero > 0) {
                        maxGain = Math.max(maxGain, prevZero + nextZero);
                    }
                }
            }
        }

        return ones + maxGain;
    }
}
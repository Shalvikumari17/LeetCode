class Solution {
    public String smallestSubsequence(String s) {
        int[] last = new int[26];
        boolean[] visited = new boolean[26];

        // Store the last occurrence of every character
        for (int i = 0; i < s.length(); i++) {
            last[s.charAt(i) - 'a'] = i;
        }

        StringBuilder stack = new StringBuilder();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int index = c - 'a';

            // If character is already present, skip it
            if (visited[index]) {
                continue;
            }

            // Remove larger characters if they appear again later
            while (stack.length() > 0 &&
                   stack.charAt(stack.length() - 1) > c &&
                   last[stack.charAt(stack.length() - 1) - 'a'] > i) {

                char removed = stack.charAt(stack.length() - 1);
                stack.deleteCharAt(stack.length() - 1);
                visited[removed - 'a'] = false;
            }

            stack.append(c);
            visited[index] = true;
        }

        return stack.toString();
    }
}
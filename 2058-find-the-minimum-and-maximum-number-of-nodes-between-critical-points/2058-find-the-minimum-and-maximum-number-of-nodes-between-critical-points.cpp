class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* next = curr->next;

        int first = -1;
        int last = -1;
        int minDist = INT_MAX;

        int pos = 1;

        while (next != nullptr) {
            
            // Check if curr is a critical point
            bool critical = false;

            // Local maximum
            if (curr->val > prev->val && curr->val > next->val) {
                critical = true;
            }

            // Local minimum
            if (curr->val < prev->val && curr->val < next->val) {
                critical = true;
            }

            if (critical) {
                
                // First critical point
                if (first == -1) {
                    first = pos;
                }
                
                // If this is not the first critical point
                if (last != -1) {
                    minDist = min(minDist, pos - last);
                }

                last = pos;
            }

            prev = curr;
            curr = next;
            next = next->next;
            pos++;
        }

        // Fewer than two critical points
        if (first == last) {
            return {-1, -1};
        }

        int maxDist = last - first;

        return {minDist, maxDist};
    }
};
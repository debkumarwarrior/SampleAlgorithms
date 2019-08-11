//User function Template for C++
/*The function should return a string denoting the 
order of the words in the Alien Dictionary */
string printOrder(string dict[], int N, int k)
{
   //Your code here
   bool g[26][26] = {false};
   int indegree[20] = {0};
   for (int i = 0; i < N; i++) {
       for (int j = i + 1; j < N; j++) {
           string s1 = dict[i];
           string s2 = dict[j];
           int l1 = s1.length();
           int l2 = s2.length();
           int c1 = 0, c2 = 0;
           while ((c1 < l1) && (c2 < l2)) {
               if (s1[c1] != s2[c2]) {
                   if (g[s1[c1] - 'a'][s2[c2] - 'a'] == false) {
                       indegree[s2[c2] - 'a']++;
                       g[s1[c1] - 'a'][s2[c2] - 'a'] = true;
                   }
                   break;
               }
               c1++,c2++;
           }
       }
   }
   /*cout << "Graph: " << endl;
   for (int i = 0; i < k; i++) {
       for (int j = 0; j < k; j++) {
           cout << g[i][j] << " ";
       }
       cout << endl;
   }
   cout << "Indegree: " << endl;
   for (int i = 0; i < k; i++) {
       cout << indegree[i] << " ";
   }   
   cout << endl;*/
   string s;
   s.resize(k);
   int si = -1;
   
   int queue[26] = {0};
   int front = 0;
   int rear = -1;
   
   for (int i = 0; i < k; i++) {
       if (indegree[i] == 0) {
           rear++;
           queue[rear] = i;
       }
   }
   
   while (front <= rear) {
       /*cout << "Queue : ";
       for (int i = front; i <= rear; i++) {
           cout << queue[i] << " ";
       }
       cout << endl;*/
       int u = queue[front];
       front++;
       
       si++;
       s[si] = u + 'a';
       
       for (int v = 0; v < k; v++) {
           if (g[u][v]) {
               if (--indegree[v] == 0) {
                    rear++;
                    queue[rear] = v;
               }
           }
       }
   }
   //cout << s << endl;
   return s;
}
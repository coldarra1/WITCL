import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    static final int MAXN = 100000 + 5;
    static int [] f = new int [MAXN];
    static int [] s = new int [MAXN];
     
    static int findfa(int x) {
        if (f[x] == x) {
            return x;
        }
         
        return f[x] = findfa(f[x]);
    }
     
    static void merge(int x, int y) {
        f[x] = y;
    }
     
    public static void main(String[] args) throws IOException  {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         
        String line = in.readLine();
        int T = Integer.valueOf(line);
         
        while (T-- > 0) {
            line = in.readLine();
            String[] str = line.split(" ");
            int n = Integer.valueOf(str[0]);
            int m = Integer.valueOf(str[1]);
            int t = Integer.valueOf(str[2]);
            int cnt = 0;
             
            for (int i=1; i<=n; i++) {
                f[i] = i;
            }
             
            line = in.readLine();
            str = line.split(" ");
            for (int i=1; i<=m; i++) {
                s[i] = Integer.valueOf(str[i-1]);
            }
             
            for (int i=1; i<=t; i++) {          
                line = in.readLine();
                str = line.split(" ");
                int u = Integer.valueOf(str[0]);
                int v = Integer.valueOf(str[1]);
                 
                if (findfa(u) != findfa(v)) {
                    merge(f[u], f[v]);
                }
            }
             
            Set<Integer> st = new TreeSet<> ();
             
            for (int i=1; i<=m; i++) {
                st.add(findfa(s[i]));
            }
             
            for (int i=1; i<=n; i++) {
                if (st.contains(findfa(f[i]))) {
                    ++cnt;
                }
            }
             
            System.out.println(cnt);
        }
    }
}
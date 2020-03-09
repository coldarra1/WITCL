import java.util.*;
import java.math.*;

public class Main {
    public static void main(String[] args)  {
    	Scanner in = new Scanner(System.in);
    	int T = in.nextInt();
    	
    	while (T-- > 0) {
    		BigInteger n = in.nextBigInteger();
    		BigInteger m = in.nextBigInteger();
    		BigInteger p = in.nextBigInteger();
    		
    		BigInteger mod = n.multiply(p);         
    		
    		BigInteger t1 = q1pow(m, n, mod);		
    		BigInteger t2 = m.multiply(q1pow(m.subtract(BigInteger.valueOf(1)), n.subtract(BigInteger.valueOf(1)), mod)).mod(mod);
    												
    		System.out.println((mod.add(t1).subtract(t2)).mod(mod));
    	}
    	in.close();
    }
    
    public static BigInteger q1pow(BigInteger x, BigInteger p, BigInteger mod) {	
    	BigInteger ans = BigInteger.valueOf(1).mod(mod);
    					
    	while (p != BigInteger.valueOf(0)) {
    		if (p.mod(BigInteger.valueOf(2)) != BigInteger.valueOf(0)) {
    			ans = (ans.multiply(x)).mod(mod);	   
    		}
    		
    		x = x.multiply(x).mod(mod);
    		p = p.shiftRight(1);		
    	}
    	
    	return ans;
    }
}

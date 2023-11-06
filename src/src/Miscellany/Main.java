import java.io.*; import java.util.*; import java.math.*;
public class Main {
static class solver { public void run(Scanner cin, PrintStream out) {} }
public static void main(String[] args) {
// Decimals
BigDecimal ans, S, C;
MathContext fuckJava = new MathContext(100, RoundingMode.HALF_EVEN); 
BigDecimal minx = BigDecimal.TEN.pow(18);
C = BigDecimal.ZERO;
C.compareTo(S);
S.divide(BigDecimal.valueOf(2), fuckJava);
ans.divide(S.multiply(S), fuckJava).multiply(new BigDecimal(2));
System.out.println(new DecimalFormat("0.000000000").format(ans));
// Fast Reader & Big Numbers
InputReader in = new InputReader(System.in);
PrintWriter out = new PrintWriter(System.out);
BigInteger c = in.nextInt();
out.println(c.toString(8)); out.close(); // as Oct
BigDecimal d = new BigDecimal(10.0);
// d=d.divide(num, length, BigDecimal.ROUND_HALF_UP)
d.setScale(2, BigDecimal.ROUND_FLOOR); // 用于输出
System.out.printf("%.6f\n", 1.23); // C 格式
BigInteger num = BigInteger.valueOf(6);
num.isProbablePrime(10); // 1 - 1 / 2 ^ certainty
BigInteger rev = num.modPow(BigInteger.valueOf(-1), BigInteger.valueOf(25));  // rev=6^-1mod25 要互质
num = num.nextProbablePrime(); num.intValue();
Scanner cin=new Scanner(System.in);//SimpleReader
int n = cin.nextInt();
int [] a = new int [n]; // 初值未定义
// Random rand.nextInt(N) [0,N)
Arrays.sort(a, 5, 10, cmp); // sort(a+5, a+10)
ArrayList<Long> list = new ArrayList(); // vector
// .add(val) .add(pos, val) .remove(pos)
Comparator cmp=new Comparator<Long>(){ // 自定义逆序
  @Override public int compare(Long o1, Long o2) {
  /* o1 < o2 ? 1 :( o1 > o2  ? -1 : 0) */ } };
// Collections. shuffle(list) sort(list, cmp)
Long [] tmp = list.toArray(new Long [0]);
// list.get(pos) list.size()
Map<Integer,String> m = new HashMap<Integer,String>();
//m.put(key,val) get(key) containsKey(key) remove(key)
for (Map.Entry<Integer,String> entry:m.entrySet()); //entry.getKey() getValue()
Set<String> s = new HashSet<String>(); // TreeSet
//s.add(val)contains(val)remove(val);for(var : s)
solver Task=new solver();Task.run(cin,System.out);
PriorityQueue<Integer> Q=new PriorityQueue<Integer>();
// Q. offer(val) poll() peek() size()
// Read / Write a file : FileWriter FileReader PrintStream
} static class InputReader { // Fast Reader
public BufferedReader reader;
public StringTokenizer tokenizer;
public InputReader(InputStream stream) {
	reader = new BufferedReader(new InputStreamReader(stream), 32768);
	tokenizer = null; }
public String next() {
	while (tokenizer==null||!tokenizer.hasMoreTokens()) {
		try { String line = reader.readLine();
			/*line == null ? end of file*/
			tokenizer = new StringTokenizer(line);
		} catch (IOException e) {
			throw new RuntimeException(e); }
	} return tokenizer.nextToken(); }
public BigInteger nextInt() {
	//return Long.parseLong(next()); Double Integer
	return new BigInteger(next(), 16); // as Hex
} } }

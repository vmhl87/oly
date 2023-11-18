import java.io.*;
import java.util.*;

public class alchemy {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

		int n = Integer.parseInt(in.readLine());
		int[] metals = new int[n];

		StringTokenizer st = new StringTokenizer(in.readLine());
		for(int i=0; i<n; i++) {
			metals[i] = Integer.parseInt(st.nextToken());
		}

		int k = Integer.parseInt(in.readLine());
		Map<Integer, List<Integer>> recipies = new HashMap<>();
		for (int i=0; i<k; i++) {
			st = new StringTokenizer(in.readLine());
			int l = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());

			List<Integer> ingredients = new ArrayList<>();
			for (int j=0; j<m; j++) {
				ingredients.add(Integer.parseInt(st.nextToken()) - 1);
			}

			recipies.put(l-1, ingredients);
		}

		// initial recipe set to make metal n is just to use 1 unit of n itself
		int[] current = new int[n];
		current[n-1] = 1;

		int ret = 0;
		boolean finished = false;

		while (!finished) {
			// find the maximum units of metal N we can create with our current recipe set
			int canMake = Integer.MAX_VALUE;
			for (int i=0; i<n; i++) {
				if (current[i] > 0) {
					canMake = Math.min(canMake, metals[i]/current[i]);
				}
			}

			// reduce our amount of metals by appropriate amount
			ret += canMake;
			for (int i=0; i<n; i++) {
				metals[i] -= canMake * current[i];
			}

			// for each metal in our current recipe set that we don't have enough of, find a recipe that
			// can produce this metal and update the recipe set to match
			for (int i=0; i<n; i++) {
				if (current[i] > metals[i]) {
					if (recipies.containsKey(i)) {
						// if we still have some amount of metal i in our storage, but just
						// not enough to make a full unit of metal n, we can try to create
						// just enough of metal i from its sources
						for (int h : recipies.get(i)) current[h] += current[i] - metals[i];
						current[i] = metals[i];
					} else {
						finished = true; break;
					}
				}
			}
		}

		System.out.println(ret);
	}
}

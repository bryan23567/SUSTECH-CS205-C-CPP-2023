import java.util.Random;

public class Main {
    public static void main(String[] args) throws Exception {
        for (int n = 1; n < 1000000000; n *= 10) {
            float vec1[] = new float[n];
            float vec2[] = new float[n];
            Random r = new Random();
            for (int i = 0; i < n; i++) {
                vec1[i] = 1 + r.nextFloat() * (9);
                vec2[i] = 1 + r.nextFloat() * (9);
            }
            long start = System.nanoTime();
            float total = 0;
            for (int i = 0; i < n; i++) {
                total += vec1[i] * vec2[i];
            }
            long stop = System.nanoTime();
            float lenghtV1 = 0;
            for (int i = 0; i < n; i++) {
                lenghtV1 += vec1[i] * vec1[i];
            }

            float lenghtV2 = 0;
            for (int i = 0; i < n; i++) {
                lenghtV2 += vec2[i] * vec2[i];
            }

            lenghtV1 = (float) Math.sqrt(lenghtV1);
            lenghtV2 = (float) Math.sqrt(lenghtV2);

            System.out.printf(
                    "Vector1 with lenght: %f and Vector2 with lenght: %f the result is %f takes time %d nanoseconds\n",
                    lenghtV1, lenghtV2, total,
                    (stop - start));
        }
    }
}

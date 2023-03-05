import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

/*
 * reads a sequence of words from standard input and prints one of those words uniformly at random. 
 * Do not store the words in an array or list. Instead, use Knuth’s method: when reading the ith word, 
 * select it with probability 1/i  to be the champion, replacing the previous champion. 
 * After reading all of the words, print the surviving champion.
 */

// This one tests a bit of maths skills. Probability formulas must be used.

public class RandomWord {
    public static void main(String[] args){
        int sum = 0;
        String champ = "", candidate;
        while(!StdIn.isEmpty()){
            candidate = StdIn.readString();
            if(StdRandom.bernoulli(1/(1.0+sum))){
                champ = candidate;
            }
            sum++;
        }
        System.out.println(champ);
    }
}


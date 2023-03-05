import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

/*
 * reads a sequence of words from standard input and prints one of those words uniformly at random. 
 * Do not store the words in an array or list. Instead, use Knuth’s method: when reading the ith word, 
 * select it with probability 1/i  to be the champion, replacing the previous champion. 
 * After reading all of the words, print the surviving champion.
 */

// a little bit of  math problem here:
// for i-th element, prob is 1/f(i)
// such that 1/f(i) / (1/f[1]+1/f[2]+ ... + 1/f[n]) = 1/n

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


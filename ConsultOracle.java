import java.util.Scanner;
import java.util.Map;
import org.jpl7.Query;
import org.jpl7.Term;

public class ConsultOracle {
    public static void consultOracle(String tag) {
        String t1 = "consult('master.pl')";
        Query q1 = new Query(t1);
        System.out.println(t1 + " " + (q1.hasSolution() ? "Consulta ao oráculo iniciada!" : "Houve algum erro!"));
        String t4 = "desafio("+tag+",Y)";
        Query q4 = new Query(t4);
		q4.hasMoreSolutions();
        Map<String, Term> s5 = q4.nextSolution();
        Term test = s5.get("Y");
        System.out.println(test.toString());
        if(test.toString().equalsIgnoreCase("conhecimento")){
            System.out.println("oi");
        }
        System.out.println(tag);
    }
}
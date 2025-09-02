public class PrecoUtils {
    private PrecoUtils() {}

    // Aplica um desconto percentual a um preço.
    public static double aplicarDesconto(double preco, double percentual) {
        if (percentual < 0) {
            System.out.println("Percentual de desconto negativo. Nenhum desconto será aplicado.");
            return preco;
        }
        double valorDesconto = preco * (percentual / 100);
        return preco - valorDesconto;
    }

    // Aplica um desconto absoluto a um preço.
    public static double aplicarDesconto(double preco, int valorAbsoluto) {
        if (valorAbsoluto < 0) {
            System.out.println("Valor de desconto absoluto negativo. Nenhum desconto será aplicado.");
            return preco;
        }
        
        double novoPreco = preco - valorAbsoluto;
        if (novoPreco < 0) {
            return 0.0;
        }
        return novoPreco;
    }
}
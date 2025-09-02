public class App {
    public static void main(String[] args) {
        Produto.setDescontoGlobal(5);
        Produto[] produtos = new Produto[5];
        for (int i = 0; i < produtos.length; i++) {
            double preco = 100.0 + (i * 20);
            produtos[i] = new Produto("Nome " + (i + 1), preco);
        }

        System.out.println("=============================================");
        System.out.println("Total de Produtos criados: " + Produto.getTotalCriados());
        System.out.println("=============================================");

        for (Produto p : produtos) {
            System.out.println("\n--- Detalhes do Produto ---");
            System.out.println(p.toString());

            // Desconto Percentual
            double precoComDescontoPct = PrecoUtils.aplicarDesconto(p.getPreco(), Produto.DESCONTO_GLOBAL);
            System.out.printf("Preço com desconto global (%.1f%%): R$ %.2f%n", Produto.DESCONTO_GLOBAL, precoComDescontoPct);

            // Desconto Absoluto
            int descontoAbsoluto = 10;
            double precoComDescontoAbs = PrecoUtils.aplicarDesconto(p.getPreco(), descontoAbsoluto);
            System.out.printf("Preço com desconto absoluto (R$ %d): R$ %.2f%n", descontoAbsoluto, precoComDescontoAbs);
        }
    }
}
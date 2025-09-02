public class Produto {
    private String nome;
    private double preco;

    public static int totalCriados = 0;
    public static double DESCONTO_GLOBAL = 0.0;

    public Produto (){
        setNome("Sem nome");
        setPreco(0.0);
    }

    public Produto (String nome, double preco){
        this.setNome(nome);
        this.setPreco(preco);
        totalCriados++;
    }

    public static int getTotalCriados() {
        return totalCriados;
    }

    public static double getDescontoGlobal() {
        return DESCONTO_GLOBAL;
    }

    public static void setDescontoGlobal(double desconto) {
        if(desconto >= 0 && desconto <= 50) {
            DESCONTO_GLOBAL = desconto;
        } else {
            System.out.println("Desconto inválido. O desconto deve estar entre 0 e 50.");
        }
    }

    public String getNome() {
        return nome;
    }

    public double getPreco(){
        return preco;
    }

    public void setNome(String nome) {
        if(nome != null && !nome.trim().isEmpty()) {
            this.nome = nome;
        } else {
            System.out.println("Nome inválido. O nome não deve ser vazio.");
        }
    }

    public void setPreco(double preco) {
        if(preco >= 0) {
            this.preco = preco;
        } else {
            System.out.println("Preço inválido. O preço não deve ser negativo.");
        }
    }

    public String toString(){
        return String.format("Nome: %s, Preço Original: R$ %.2f", this.nome, this.preco);
    }

}

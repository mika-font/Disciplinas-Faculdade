public class Pessoa {
    private String nome;
    private String endereco;
    private int idade;

    public Pessoa (String nome, String endereco, int idade){
        this.nome = nome;
        this.endereco = endereco;
        this.idade = idade;
    }

    public void alterarEndereco(String newEndereco){
        if(newEndereco != endereco && newEndereco != null){
            this.endereco = newEndereco;
        } else {
            System.out.println("Erro ao atualizar endereço. Campo vazio ou inválido.");
        }
    }

    public void getPessoa(){
        System.out.print("Nome: " + nome + "\n Endereco: " + endereco + "\n Idade: " + idade + "\n");
    }

    public static void main(String[] args) {
        Pessoa pessoa1 = new Pessoa("Mikael", "Duque de Caxias, 1263", 20);
        Pessoa pessoa2 = new Pessoa("Angela", "Silva Jardim, 1221", 22);

        pessoa1.getPessoa();
        pessoa2.getPessoa();

        pessoa1.alterarEndereco("Marechal Deodoro, 4490");
        pessoa1.getPessoa();

        pessoa2.alterarEndereco(null);
        pessoa2.getPessoa();
    }
}
public class Membros {
    private String nome;
    private String email;
    private String telefone;
    private String cargo;
    private int matricula;

    public Membros(String nome, String email, String telefone, String cargo, int matricula) {
        this.nome = nome;
        this.email = email;
        this.telefone = telefone;
        this.cargo = cargo;
        this.matricula = matricula;
    } 

    public String getNome() {
        return nome;
    }
    public String getEmail() {
        return email;
    }
    public String getTelefone() {
        return telefone;
    }
    public String getCargo() {
        return cargo;
    }
    public int getMatricula() {
        return matricula;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }
    public void setEmail(String email) {
        this.email = email;
    }
    public void setTelefone(String telefone) {
        this.telefone = telefone;
    }
    public void setCargo(String cargo) {
        this.cargo = cargo;
    }
    public void setMatricula(int matricula) {
        this.matricula = matricula;
    }

    public String exibirMembro(){
        return "Nome: " + nome + ", Email: " + email + ", Telefone: " + telefone + ", Cargo: " + cargo + ", Matrícula: " + matricula;
    }

    //teste
    public static void main(String[] args) {
        Membros membro1 = new Membros("Ana Silva", "ana@email.com", "1234-5678", "Gerente", 1);
        System.out.println(membro1.exibirMembro());
    }
}
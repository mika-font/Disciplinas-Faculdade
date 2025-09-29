public class Funcionario {
    private String nome;
    private String departamento;
    private float salario;

    public Funcionario(String nome, String departamento, float salario) {
        setNome(nome);
        setDepartamento(departamento);
        setSalario(salario);
    }

    public String getNome() {
        return nome;
    }

    public String getDepartamento() {
        return departamento;
    }

    public float getSalario() {
        return salario;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public void setDepartamento(String departamento){
        this.departamento = departamento;
    }

    public void setSalario(float salario){
        this.salario = salario;
    }

    public void aumentarSalario(float percentual) {
        if (percentual > 0) {
            salario += salario * (percentual / 100);
        }
    }
}

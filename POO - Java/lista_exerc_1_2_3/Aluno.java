public class Aluno {
    private String nome;
    private int matricula;
    private String[] disciplinasCursadas = new String[10];

    public Aluno(String nome, int matricula) {
        this.nome = nome;
        this.matricula = matricula;
    }

    public String getNome() {
        return nome;
    }

    public int getMatricula() {
        return matricula;
    }

    public String[] getDisciplinasCursadas() {
        return disciplinasCursadas;
    }

    public void adicionarDisciplina(String disciplina) {
        for (int i = 0; i < disciplinasCursadas.length; i++) {
            if (disciplinasCursadas[i] == null) {
                disciplinasCursadas[i] = disciplina;
                break;
            }
        }
    }
    public float mediaNotas(float[] notas) {
        float soma = 0;
        for (float nota : notas) {
            soma += nota;
        }
        return soma / notas.length;

    }
    public static void main(String[] args) {
        Aluno aluno = new Aluno("João", 123);
        aluno.adicionarDisciplina("Matemática");
        aluno.adicionarDisciplina("Português");

        System.out.println("Nome: " + aluno.getNome());
        System.out.println("Matrícula: " + aluno.getMatricula());
        System.out.println("Disciplinas Cursadas: ");
        for (String disciplina : aluno.getDisciplinasCursadas()) {
            if (disciplina != null) {
                System.out.println(" - " + disciplina);
            }
        }

        float[] notas = {7.5f, 8.0f, 6.5f};
        System.out.println("Média das Notas: " + aluno.mediaNotas(notas));
    }
}

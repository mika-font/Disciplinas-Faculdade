public class Livro {
    private String autor;
    private int ano;
    private String titulo;
    private boolean reservado;

    public Livro(String autor, int ano, String titulo){
        this.titulo = titulo;
        this.autor = autor;
        this.ano = ano;
        this.reservado = false;
    }

    public void emprestar(){
        System.out.println("Livro emprestado.");
        this.reservado = true;
    }

    public void devolver(){
        System.out.println("Livro devolvido.");
        this.reservado = false;
    }
}
#include <iostream>
#include <string>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

using namespace std;

//Versão do certificado
int certversion(X509* x509)
{
    return X509_get_version(x509);
}

//colocando o subject em ASCII
string _subject_as_line(X509_NAME *subj_or_issuer)
{
    BIO * bio_out = BIO_new(BIO_s_mem()); //ponteiro inicializando BIO
    X509_NAME_print(bio_out,subj_or_issuer,0);//função print para retirar os valores do ponteiro do certificado
    BUF_MEM *bio_buf; //buffer BIO
    BIO_get_mem_ptr(bio_out, &bio_buf);//passando o conteudo de bio_out para bio_buff
    string issuer = string(bio_buf->data, bio_buf->length);//convertendo para string/ascii
    BIO_free(bio_out);//liberando a memoria
    return issuer;//retorna string com o issuer/subject
}

//pega a linha Issuer
string issuer_one_line(X509* x509){
    return _subject_as_line(X509_get_issuer_name(x509));
}
//pega a linha Subject
string subject_one_line(X509* x509){
    return _subject_as_line(X509_get_subject_name(x509));
}

//pega os dados do certificado e concatena em uma string
string cert(X509 *x509){
    string teste = "Version:  " + to_string(certversion(x509)) + "\nIssuer: " + issuer_one_line(x509) + "\nSubject: "+
                   subject_one_line(x509);
    return teste;
}



int main(int argc, char** argv)
{
    OpenSSL_add_all_algorithms();

    if (argc < 2)//verifica o arquivo argumento na pasta raiz do projeto
    {
        cout << "Missing filename" << endl;
        return 1;
    }

    string inFile(argv[1]);//primeiro argumento do vetor

    BIO *file = BIO_new(BIO_s_file());//cria um novo BIO para verificação de arquivo
    if(BIO_read_filename(file,inFile.c_str())<=0){
        cout<< "erro ao ler arquivo" << endl;
        return 1;
    }

    X509 *x509 = PEM_read_bio_X509(file,NULL,NULL,NULL);//passa a leitura do certificado para um ponteiro do tipo X509
    string data = cert(x509);
    cout << data << endl;//mostra os dados em ascii na tela


    return 0;
}

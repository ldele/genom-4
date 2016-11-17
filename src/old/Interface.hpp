#ifndef interface_H
#define interface_H

#include "DNA.hpp"
#include "PWM.hpp"

/*!
 * External function
 * Convertit A, C, G, T en coordonnée dans PWM/colonne dans la matrice
 */
size_t const convert(char const&);

/*!
 * Struct (-> peut mieux faire...)
 * Tout ce qu'il faut savoir sur les séquences retenuent
 * Champ1 nom du brin, seq1 par défaut/j'ai fait comme s'il n'y avait qu'un brin sans >chr7|chr7:113842207-113842607 ou autre
 * Champ2 la séquence
 * Champ3 numéro de la premiere base de la séquence (place dans le brin)
 * Champ4 score de la séquence
 * Champ5 '+' si fwd ou '-' si Rev (-> peut mieux faire)
 */
struct OutputSeqData
{
    std::string Strand = "seq1";
    std::string Seq;
    size_t Number;
    double Score = 0.0;
    char Fwd = '+';
};

/*! Interface class */
class Interface
{
public:
    /*!
     * Constructeur
     * A besoin du nom des fichiers
     */
    Interface(std::string const&, std::string const& = "output.fasta", std::string const& = "DBP_PPM.mat");

    /*!
     * Public Function
     * Change le fichier PWM
     */
    bool setPWM(std::string const&);

    /*!
     * Public Function
     * Change le fichier DNA
     */
    bool setDNA(std::string const&);

    /*!
     * Public Function
     * Change le fichier d'output
     */
    bool setOut(std::string const&);

    /*!
     * Public Function
     * Change le seuil (-> cette fonction est mal pensée)
     */
    void setThreshold(double const&);

    /*!
     * Public Function
     * Check si le fichier existe et s'il s'ouvre correctement. Flux d'entrée...
     */
    bool checkIfFile(std::string const&, std::string const& = ".fasta") const;

    /*!
     * Public Function
     * Crée le fichier s'il n'existe pas. Check si c'est bien un .fasta
     */
    bool checkOfFile(std::string const&, std::string const& = ".fasta") const;

    /*!
     * Public Function
     * Si tout se passe bien, exécute le programme sinon ne fait rien.
     * -> si les fichiers ont pu s'ouvrir et qu'il n'y a pas de soucis dans PWM et/ou DNA.
     */
    void output();

private:
    DNA mDNA; /*!< DNA */
    PWM mPWM; /*!< PWM */
    std::string mDNAFileN; /*!< Nom du fichier DNA */
    std::string mPWMFileN; /*!< Nom du fichier PWM */
    std::string mOutFileN; /*!< Nom du fichier de sortie (output) */
    double threshold; /*!< Seuil, on ne garde que les sequences qui ont un score supérieur */
    std::vector<OutputSeqData> mDNAandPWM; /*!< Enregistre l'output, voir OutputSeqData */

    /*!
     * Private function
     * Check all files (PWM, DNA et Output)
     */
    bool checkFiles() const;

    /*!
     * Private function
     * Aide la fonction Interface::output
     */
    bool FromDNAandPWM();

    /*!
     * Private function
     * Aide Interface::FromDNAandPWM
     */
    void calcScore(OutputSeqData&, std::ofstream&);
};

#endif


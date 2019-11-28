:- dynamic nome/1.
:- dynamic persona/1.
:- dynamic desafio_aceitacao/1.
:- dynamic treina/1.
:- dynamic melhoramento/1.
:- dynamic desafio_luta/1.

%-----------------fatos_localiza��es------------------
localizacao(mural_valley).
localizacao(templo_sagrado).
localizacao(casa).
localizacao(casa_treinador).
localizacao(roman_disk).
localizacao(floresta_eskaroth).
localizacao(floresta_desconhecida).
localizacao(floresta).
localizacao(floresta_passage_um).
localizacao(floresta_passage_dois).
localizacao(floresta_passage_tres).
localizacao(montanha).

%------------------fatos_desafios--------------------
desafio(mural_valley, direita).
desafio(templo_sagrado, heal).
desafio(casa, esconder).
desafio(casa, lutar).
desafio(roman_disk, desafios).
desafio(casa_treinador, vinganca).
desafio(casa_treinador, perdoar).
desafio(floresta, faro).
desafio(floresta, forca).
desafio(floresta_desconhecida, faro).
desafio(floresta_desconhecida, forca).
desafio(montanha, respiracao).
desafio(montanha, energia).
desafio(floresta_eskaroth, concentracao).
desafio(floresta_eskaroth, forca).
desafio(floresta_passage_um, conhecimento).
desafio(floresta_passage_dois, conhecimento).
desafio(floresta_passage_tres, conhecimento).

%--------------personalidades--------------
atributos(perceber, intuir).
atributos(sentir, pensar).
atributos(perceber, pensar).
atributos(sentir, intuir).

%-----------Desafios de treinamento--------
treina(estrategia) :- desafio(teste, concentracao).
treina(luta) :- desafio(floresta, forca), desafio(teste, forca).
treina(corpo) :- desafio(montanha, respiracao), desafio(montanha, energia).
treina(sentidos) :- desafio(floresta, faro).

%-----------------fatos_treinamentos-------------------
adquiri(inteligencia) :- treina(estrategia).
adquiri(forca) :- treina(luta).
adquiri(vitalidade) :- treina(corpo).
adquiri(destreza) :- treina(sentidos).
persona(impulsivo) :- atributos(perceber, intuir), atributos(sentir, intuir).
persona(perceptivo) :- atributos(sentir, pensar), atributos(perceber, pensar).


%-----------Desafio de luta-----------
desafio_luta(aceito) :- desafio_aceitacao(aceito), reposta_desafio_luta(calculista).
desafio_luta(rejeitado) :- reposta_desafio_luta(sentimentos).

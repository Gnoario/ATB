{-# LANGUAGE ForeignFunctionInterface #-}

module Ataque where

    import Data.Bool
    import Foreign.C.Types
    
    damageArmor :: Int -> Int -> Int  -- escolha do escudo que interfere diretamente na quantidade de dando que o personagem irá receber
    damageArmor damage armor
     |armor==0 = damage - 5
     |armor==1 = damage - 10
     |armor==2 = damage - 15
     
    
    sub_defence :: Int -> Int -> Int -> Int -> Int  -- funçao de defesa do personagem
    sub_defence  health armor damage defence
     |armor <= 0 = health - (damage - defence)
     |otherwise = armor - damage 
     
    npc:: Int -> Int -> Int
    npc health potion
     |health <30 && health>0 = health + potion 
     |otherwise = health + 0
    
    
    --Gerar um número aleatório entre 1 e 20 em C e passar como parâmetro
    --Se o numero aleatorio for 20 dobra o dano, se for menor retorna o dano normal
    criticoDamage :: Int -> Int -> Int
    criticoDamage dano critChance 
     | critChance == 20 = dano*2
     | otherwise = dano
     
    --Gerar um número aleatório entre 1 e 100 em C e passar como parâmetro
    --Se retornar true o ataque acontece, se retornar false o ataque erra
    dexHitChance :: Int -> Int -> Bool
    dexHitChance dex hit 
     | (dex <= 6) && (hit <=60) = True
     | (dex >= 7) && (dex <= 10) && (hit <=70) = True
     | (dex >= 11) &&  (dex <= 14) && (hit <=80) = True
     | (dex >= 15) &&  (dex <= 18) && (hit <=90) = True
     | (dex >= 19) &&  (dex <= 22) && (hit <=100) = True
     | otherwise = False
    
     
     -- ataques 
     
     --Ataques básicos
    atkBasico :: Int -> Int -> Int
    atkBasico dano str = dano + str
    
    -- Concentração
    concentracaoF :: Int -> Int 
    concentracaoF dano = dano + 10
     
    --Meditar
    meditarF :: Int -> Int 
    meditarF vidaMaxima = vidaMaxima + 100
    
    -- Corte Giratorio
    corteGir :: Int -> Int -> Int 
    corteGir dano str = dano + str + 30
    
    --Bola de fogo
    fireBall :: Int -> Int -> Int 
    fireBall dano int = dano + int + 40
    
    --Heal 
    heal :: Int -> Int -> Int 
    heal vida int = vida + 10 + int
    
    -- Tempestade de aço
    tempAco :: Int -> Int -> Int 
    tempAco dano str = dano + str + 50
    
    -- Cometa arcano 
    comArc :: Int -> Int -> Int 
    comArc dano int = dano + int + 60
    
    --Posição Kamaitachi
    posKamai :: Int -> Int -> Int 
    posKamai dano str = dano + str + 200
    
    foreign export ccall concentracaoF :: Int -> Int
    foreign export ccall meditarF :: Int -> Int
    foreign export ccall fireBall :: Int -> Int -> Int
    foreign export ccall heal :: Int -> Int -> Int
    foreign export ccall comArc :: Int -> Int -> Int
    foreign export ccall criticoDamage :: Int -> Int -> Int
    foreign export ccall dexHitChance :: Int -> Int -> Bool
    foreign export ccall atkBasico :: Int -> Int -> Int
    foreign export ccall corteGir :: Int -> Int -> Int
    foreign export ccall tempAco :: Int -> Int -> Int
    foreign export ccall posKamai :: Int -> Int -> Int
    foreign export ccall sub_defence :: Int -> Int -> Int -> Int -> Int
    foreign export ccall damageArmor :: Int -> Int -> Int
    foreign export ccall npc:: Int -> Int -> Int
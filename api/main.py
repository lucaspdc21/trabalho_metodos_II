from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
from fastapi.middleware.cors import CORSMiddleware
from typing import List
import json

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  
    allow_credentials=True,
    allow_methods=["*"],  
    allow_headers=["*"], 
)

class Iteracao(BaseModel):
    iteracao: int
    valores: List[float]

class Resultado(BaseModel):
    Ainv: List[List[float]]
    deslocamentos: List[float]
    iteracoes: List[Iteracao]

@app.get("/dados")
def obter_dados():
    try:
        with open("../resultado.json", "r") as arquivo:
            dados = json.load(arquivo)
        return dados
    except FileNotFoundError:
        raise HTTPException(status_code=404, detail="Arquivo de dados não encontrado.")
    except json.JSONDecodeError:
        raise HTTPException(status_code=500, detail="Erro ao ler o arquivo JSON.")

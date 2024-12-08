import asyncio
from fastapi import FastAPI, HTTPException, APIRouter
from pydantic import BaseModel

app = FastAPI()
api_router = APIRouter(prefix="/api")

@api_router.get('/')
async def root():
    return {"Hello": "World"}

@api_router.post('/client')
async def compile_client():
    # Implement client compiler code

@api_router.post('/server')
async def compile_server():
    # Implement server compiler code
    
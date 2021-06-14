import aiohttp
import asyncio

async def fetch(client):
    async with client.get('http://localhost:5000') as resp:
        assert resp.status == 200
        return await resp.text()

async def fetch1(client):
    async with client.get('http://localhost:5000') as resp:
        assert resp.status == 200
        return await resp.text()

async def fetch2(client):
    async with client.get('http://localhost:5000') as resp:
        assert resp.status == 200
        return await resp.text()


async def main():
    cl_tm = aiohttp.ClientTimeout(60)
    cl_bc = aiohttp.BaseConnector(keepalive_timeout=100, limit=200)
    async with aiohttp.ClientSession(connector=cl_bc, timeout=cl_tm, header) as client:
        print(dir(client))
        print(client.headers)
        for x in client.headers:
            print(x)
        html1 = await fetch(client)
        html2 = await fetch1(client)
        html3 = await fetch2(client)
        print(html1)
        print(html2)
        print(html3)

loop = asyncio.get_event_loop()
loop.run_until_complete(main())

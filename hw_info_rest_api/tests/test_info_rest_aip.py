import dataclasses

import pytest
import requests
import schema

import misc
from misc import rest_api_host, rest_api_port


@dataclasses.dataclass
class Data:
    url: str
    json_schema: schema.Schema


endpoints = [
    Data(url=f'http://{rest_api_host}:{rest_api_port}/ipv4', json_schema=misc.ipv4_schema),
    Data(url=f'http://{rest_api_host}:{rest_api_port}/meminfo', json_schema=misc.meminfo_schema),
    Data(url=f'http://{rest_api_host}:{rest_api_port}/hddinfo', json_schema=misc.hddinfo_schema),
    Data(url=f'http://{rest_api_host}:{rest_api_port}/cpuinfo', json_schema=misc.cpuinfo_schema)

]


@pytest.mark.parametrize("endpoint_data", endpoints)
def test_ipv4(endpoint_data):
    response = requests.get(endpoint_data.url)
    assert response.status_code == 200
    body = response.json()
    assert misc.check_body(body, endpoint_data.json_schema)


if __name__ == '__main__':
    test_ipv4()

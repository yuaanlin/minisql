# MiniSQL

A simple SQL engine, as a course project in "Database Design" course at Zhejiang Univ.

## Build

```bash
clang++ -std=c++17 **/*.cpp -o main
```

## Run

```bash
./main
```

## Example

Send `POST` request tp port `3306` with SQL command in request body.

You can use our [MiniSQL Client](https://github.com/ken20001207/MiniSQL-Client) to send query.

![](https://github.com/ken20001207/MiniSQL-Client/blob/main/screenshot.png)

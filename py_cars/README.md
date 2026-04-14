## Prepare environment

```bash
python -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

## Fetch cars from avby

```bash
python fetch/main.py
```

## Parse and filter apartments and store to a file

```bash
python process/main.py
```

## Analyse in analyse/main.ipynb

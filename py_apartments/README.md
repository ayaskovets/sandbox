## Prepare environment

```bash
python -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

## Fetch apartments from onliner

```bash
python src/script_create_snapshot.py
```

## Parse and filter apartments and store to a file

```bash
python src/script_parse_snapshot.py
```

**Overview**

Questo documento riassume le modifiche fatte per generalizzare l'implementazione dell'algoritmo Ford–Johnson (`PmergeMe`) in modo C++98-compatible, cosa è stato mantenuto, come usare la nuova API e quali passi restano da completare.

**Cosa ho fatto**
- Reso `Element` generico rispetto al tipo degli elementi (uso di `std::iterator_traits` per `value_type`). File: [Element.hpp](Element.hpp)
- Aggiunto un'implementazione templata in `PmergeMe_impl.hpp` che incapsula la logica originale in `PmergeMeEngine<Cont,T,Alloc>` e conta le comparazioni per istanza.
- Aggiunto due interfacce templated utili:
  - `ford_johnson_template<Cont,T,Alloc>(sequence)` — restituisce il container ordinato.
  - `ford_johnson_with_count_template<Cont,T,Alloc>(sequence, outComparisons)` — restituisce il container e mette il numero di comparazioni in `outComparisons`.
- Mantenuta compatibilità con l'API esistente: wrapper non-templati in `PmergeMe.cpp` per `std::deque<int>`:
  - `ford_johnson(std::deque<int>)`
  - `ford_johnson_with_count(std::deque<int>, unsigned long &)`
- Aggiornato `main.cpp` con esempi d'uso per `std::deque<int>` e `std::vector<int>` che mostrano come ottenere anche il conteggio delle comparazioni.
- Compilazione verificata con `make` (opzione `--std=c++98`) — build riuscita.

**Principi seguiti**
- Nessuna modifica alla logica dell'algoritmo: ho migrato e incapsulato il codice esistente in modo che il comportamento rimanga identico.
- Contatore comparazioni: scelto per-instance (separato per ogni invocazione/istanza), come da preferenza comunicata.
- Compatibilità C++98: nessuna caratteristica C++11 usata nella versione finale compilata.

**Dove cercare le modifiche**
- [Element.hpp](Element.hpp)
- [PmergeMe_impl.hpp](PmergeMe_impl.hpp)
- [PmergeMe.cpp](PmergeMe.cpp)
- [main.cpp](main.cpp) (esempi di invocazione)

**Esempi di utilizzo**

- Usare la comoda wrapper per `std::deque<int>` (compatibile con il codice precedente):

```cpp
std::deque<int> dq = extractNumbersDeque(input);
unsigned long comparisons = 0;
std::deque<int> sorted = ford_johnson_with_count(dq, comparisons);
std::cout << "comparisons: " << comparisons << std::endl;
```

- Usare la versione templata per `std::vector<int>`:

```cpp
std::vector<int> v = extractNumbers(input);
unsigned long comparisons = 0;
std::vector<int> sorted = ford_johnson_with_count_template< std::vector, int, std::allocator<int> >(v, comparisons);
```

Nota: le funzioni templated richiedono il template-template parameter `Cont` (es. `std::vector` o `std::deque`) e il tipo `T`.

**Cosa manca / prossimi passi raccomandati**
1. API più comoda per utenti C++98: fornire helper overload templated che deducano `T` automaticamente (limitato in C++98) o aggiungere wrapper per `std::vector<int>` e altri container comuni per evitare di scrivere la firma template esplicita.
2. Pulizia `debugUtils`: generalizzare o rimuovere le funzioni hard-coded che lavorano solo con `std::deque<int>` e fornire overload generici di stampa per container.
3. Esposizione del motore/istanza: attualmente `ford_johnson_template` crea internamente un `PmergeMeEngine` e restituisce solo la sequenza. Se vuoi esporre `engine.comparisons` direttamente o altri metrics, potrei aggiungere una classe pubblica con metodi `run()` e `getComparisons()` per accesso post-run.
4. Test coverage: aggiungere alcuni unit test (piccoli harness) che confrontino l'output pre-refactor e post-refactor su più input.
5. Supporto a più container: aggiungere wrapper per `std::list` (attenzione: `list` non è random-access — il codice usa operator+ e distance su iteratori; questo richiede adattamenti) o documentare che i container supportati devono essere random-access (`operator+` usato).

**Note tecniche e limitazioni**
- Il codice richiede che il container passato supporti operazioni come `begin()`, `end()`, `insert(end, first, last)`, `insert(position, value)`, `erase(iterator)`, `push_back`, ed operazioni di iterazione random-access (uso di `operator+` e `std::distance` con assunzione di supporto efficiente). Di conseguenza `std::vector` e `std::deque` sono supportati; `std::list` richiederebbe modifiche.
- La conta delle comparazioni è incrementata solo quando vengono effettuate le comparazioni tra valori degli elementi nell'algoritmo (wrapper `cmpGreater` e `cmpLessEqual`). Operazioni che coinvolgono spostamenti o swap non sono contate.

**Comandi utili**

Per ricompilare ed eseguire (cartella di lavoro del progetto):

```sh
make
./PmergeMe "7 3 9 1 4"
```

Se vuoi che implementi subito una API wrapper per `std::vector<int>` e/o renda `debugUtils` generico, dimmelo e procedo con le modifiche successive.

-- Fine

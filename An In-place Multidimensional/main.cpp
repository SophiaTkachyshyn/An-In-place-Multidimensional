#include <iostream>
#include <vector>

template <typename T = char>
size_t CreateArrayAtMemory(void* p, size_t bs)
{
    return bs * sizeof(T);
}

template <typename T = char, typename... Args>
size_t CreateArrayAtMemory(void* p, size_t bs, Args... args)
{
    size_t R = 0;
    size_t PS = sizeof(void*);
    char* P = static_cast<char*>(p);
    char* P0 = static_cast<char*>(p);

    size_t BytesForAllPointers = bs * PS;
    R = BytesForAllPointers;

    char* pos = P0 + BytesForAllPointers;
    for (size_t i = 0; i < bs; i++)
    {
        char** pp = reinterpret_cast<char**>(P);
        if (p)
            *pp = pos;
        size_t RLD = CreateArrayAtMemory<T>(p ? pos : nullptr, args...);
        P += PS;
        R += RLD;
        pos += RLD;
    }
    return R;
}

class MemoryManager {
private:
    void* memory_;

public:
    MemoryManager(size_t size) : memory_(malloc(size)) {}

    ~MemoryManager() {
        if (memory_ != nullptr) {
            free(memory_);
            memory_ = nullptr;
        }
    }

    void* getMemory() const {
        return memory_;
    }
};

int main() {
    int j = 0x21; // Ініціалізуємо значення для заповнення масиву

    // Створюємо пам'ять для 2 масивів
    MemoryManager memoryManager(CreateArrayAtMemory(nullptr, 6));
    void* memory = memoryManager.getMemory();

    // Виділяємо пам'ять для масивів, використовуючи std::vector
    std::vector<char> a1(CreateArrayAtMemory(memory, 6));

    // Отримуємо вказівник на виділену пам'ять
    char* f1 = a1.data();

    // Ініціалізуємо масиви деякими значеннями
    CreateArrayAtMemory(f1, 6);
    for (int i1 = 0; i1 < 6; i1++) {
        f1[i1] = j++;
    }

    // Виводимо ініціалізовані значення
    for (int i1 = 0; i1 < 6; i1++) {
        std::cout << static_cast<int>(f1[i1]) << " ";
    }
    std::cout << std::endl << a1.size() << " bytes used " << std::endl;

    return 0;
}

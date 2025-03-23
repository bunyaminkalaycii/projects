#include <stddef.h>
#include "../include/min_heap.h"

MinHeap* heap_create(size_t capacity, size_t element_size, 
                    int (*compare)(const void*, const void*)){
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = malloc(capacity * element_size);
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->element_size = element_size;
    heap->capacity = capacity;
    heap->size = 0;
    heap->compare = compare;

    return heap;
}

void heap_destroy(MinHeap* heap){
    if (!heap) return;
    
    if (heap->data) {
        free(heap->data);
    }
    free(heap);
}

int heap_insert(MinHeap* heap, const void* element) {
    if (!heap || !element) return 0;

    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        void* new_data = realloc(heap->data, new_capacity * heap->element_size);
        if (!new_data) return 0;
        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    void* target = (char*)heap->data + (heap->size * heap->element_size);
    memcpy(target, element, heap->element_size);
    heap->size++;

    size_t index = heap->size - 1;
    while (index > 0) {
        size_t parent_index = (index - 1) / 2;
        void* parent = (char*)heap->data + (parent_index * heap->element_size);
        void* current = (char*)heap->data + (index * heap->element_size);

        if (heap->compare(current, parent) < 0) {
            char temp[heap->element_size];
            memcpy(temp, current, heap->element_size);
            memcpy(current, parent, heap->element_size);
            memcpy(parent, temp, heap->element_size);
            index = parent_index;
        } else {
            break;
        }
    }

    return 1;
}

int heap_extract_min(MinHeap* heap, void* result){
    if (!heap || heap->size == 0) return 0;

    void* root = heap->data;
    memcpy(result, root, heap->element_size);

    void* last_element = (char*)heap->data + ((heap->size - 1) * heap->element_size);
    memcpy(root, last_element, heap->element_size);
    heap->size--;

    size_t index = 0;
    while (1) {
        size_t left_child = 2 * index + 1;
        size_t right_child = 2 * index + 2;
        size_t smallest = index;

        void* current = (char*)heap->data + (index * heap->element_size);
        
        if (left_child < heap->size) {
            void* left = (char*)heap->data + (left_child * heap->element_size);
            if (heap->compare(left, current) < 0) {
                smallest = left_child;
            }
        }

        if (right_child < heap->size) {
            void* right = (char*)heap->data + (right_child * heap->element_size);
            void* smallest_element = (char*)heap->data + (smallest * heap->element_size);
            if (heap->compare(right, smallest_element) < 0) {
                smallest = right_child;
            }
        }

        if (smallest == index) break;

        void* smallest_element = (char*)heap->data + (smallest * heap->element_size);
        char temp[heap->element_size];
        memcpy(temp, current, heap->element_size);
        memcpy(current, smallest_element, heap->element_size);
        memcpy(smallest_element, temp, heap->element_size);

        index = smallest;
    }

    return 1;
}

int heap_peek(const MinHeap* heap, void* result){
    if (!heap || heap->size == 0) return 0;

    void* root = heap->data;
    memcpy(result, root, heap->element_size);

    return 1;
}


size_t heap_size(const MinHeap* heap){
    if (!heap) return 0;
    return heap->size;
}

int heap_merge(MinHeap* heap1, const MinHeap* heap2){
    if (!heap1 || !heap2 || heap1->element_size != heap2->element_size || !heap2->compare) return 0;

    while (heap1->size + heap2->size > heap1->capacity) {
        size_t new_capacity = heap1->capacity * 2;
        void* new_data = realloc(heap1->data, new_capacity * heap1->element_size);
        if (!new_data) return 0;
        heap1->data = new_data;
        heap1->capacity = new_capacity;
    }

    for (size_t i = 0; i < heap2->size; i++) {
        void* element = (char*)heap2->data + (i * heap2->element_size);
        heap_insert(heap1, element);
    }

    return 1;
}

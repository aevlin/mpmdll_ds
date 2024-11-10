#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char title[50];
    char artist[50];
    int duration;
    struct Node* prev;
    struct Node* next;
};

struct Node* addSong(struct Node* head, const char* t, const char* a, int d);
struct Node* removeSong(struct Node* head, const char* t);
void searchSong(struct Node* head, const char* t);
void displaySongs(struct Node* head);
void shuffleSongs(struct Node* head);

int main()
{
    struct Node* head = NULL;
    char title[50], artist[50];
    int choice, duration;

    printf("MUSIC PLAYLIST:\n");
    printf(" 1.Add a song\n 2.Remove a song\n 3.Search a song\n 4.Display the playlist\n 5.Shuffle the playlist\n 6.Exit\n");

    while(1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch(choice)
        {
            case 1:
                printf("Enter the title of song: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;

                printf("Enter the artist of song: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;

                printf("Enter the duration of song (in seconds): ");
                scanf("%d", &duration);

                head = addSong(head, title, artist, duration);
                break;

            case 2:
                printf("Enter the song title to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                head = removeSong(head, title);
                break;

            case 3:
                printf("Enter the song title to search: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                searchSong(head, title);
                break;

            case 4:
                displaySongs(head);
                break;

            case 5:
                shuffleSongs(head);
                break;

            case 6:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

struct Node* addSong(struct Node* head, const char* t, const char* a, int d)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(new_node->title, t);
    strcpy(new_node->artist, a);
    new_node->duration = d;
    new_node->prev = new_node->next = NULL;

    if(head == NULL)
    {
        head = new_node;
    }
    else
    {
        struct Node* temp = head;
        while(temp->next != NULL)
        {
        temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
    printf("Song added successfully!\n");
    return head;
}

struct Node* removeSong(struct Node* head, const char* t)
{
    if(head == NULL)
    {
        printf("Playlist is empty\n");
        return NULL;
    }

    struct Node* temp = head;

    if(strcmp(temp->title, t) == 0)
    {
        head = temp->next;
        if(head != NULL)
        {
            head->prev = NULL;
        }
        free(temp);
        printf("Song removed successfully!\n");
        return head;
    }
    while(temp != NULL && strcmp(temp->title, t) != 0)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("Song not found in playlist\n");
        return head;
    }
    if(temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    temp->prev->next = temp->next;

    free(temp);
    printf("Song removed successfully!\n");
    return head;
}
void searchSong(struct Node* head, const char* t)
{
    if(head == NULL)
    {
    printf("Playlist is empty\n");
    return;
    }

    struct Node* temp = head;
    while(temp != NULL)
    {
        if(strcmp(temp->title, t) == 0)
        {
        printf("Song found!\nTitle: %s\nArtist: %s\nDuration: %d seconds\n",
        temp->title, temp->artist, temp->duration);
        return;
        }
        temp = temp->next;
    }
    printf("Song not found in playlist\n");
}

void displaySongs(struct Node* head)
{
    if(head == NULL)
    {
        printf("Playlist is empty\n");
        return;
    }
    struct Node* temp = head;
    int count = 1;
    printf("\n=== Current Playlist ===\n");
    while(temp != NULL)
    {
        printf("%d. Title: %s\n   Artist: %s\n   Duration: %d seconds\n\n",
        count++, temp->title, temp->artist, temp->duration);
        temp = temp->next;
    }
}

void shuffleSongs(struct Node* head)
{
    if(head == NULL || head->next == NULL)
    {
        printf("Not enough songs to shuffle\n");
        return;
    }
    int count = 0;
    struct Node* temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    printf("\n=== Shuffled Playlist ===\n");
    int* visited = (int*)calloc(count, sizeof(int));
    int remaining = count;
    int current = 1;

    while(remaining > 0)
    {
        int skip = rand() % count;
        if(!visited[skip])
        {
            temp = head;
            for(int i = 0; i < skip; i++)
            {
                temp = temp->next;
            }
            printf("%d. Title: %s\n   Artist: %s\n   Duration: %d seconds\n\n",
                   current++, temp->title, temp->artist, temp->duration);
            visited[skip] = 1;
            remaining--;
        }
    }
    free(visited);
}

#include <stdio.h>
#include <stdlib.h>
struct BigInteger
{
  int data;
  struct BigInteger *next;
};

int comp(struct BigInteger *start1, struct BigInteger *start2)
{
  while (start1 && start2)
  {
    if (start1->data > start2->data)
      return 1;
    if (start1->data < start2->data)
      return -1;
    start1 = start1->next;
    start2 = start2->next;
  }
  return 0;
}

int calculate_len(struct BigInteger *head)
{
  int leng = 0;
  while (head)
  {
    head = head->next;
    leng++;
  }
  return leng;
}

int greater(struct BigInteger *start1, struct BigInteger *start2)
{
  if (calculate_len(start1) > calculate_len(start2))
  {
    return 1;
  }
  else if (calculate_len(start1) < calculate_len(start2))
  {
    return -1;
  }
  else
  {
    if (comp(start1, start2) == 1)
    {
      return 1;
    }
    else if (comp(start1, start2) == -1)
    {
      return -1;
    }
    else
    {
      return 0;
    }
  }
}


void Head(struct BigInteger **head, int key)
{
  struct BigInteger *temp =
      (struct BigInteger *)malloc(sizeof(struct BigInteger));
  if (temp == NULL)
  {
    return;
  }
  temp->data = key;
  if ((*head) == NULL)
  {
    (*head) = temp;
    temp->next = NULL;
    return;
  }
  temp->next = (*head);
  (*head) = temp;
}


void Tail(struct BigInteger **head, int key)
{
  struct BigInteger *temp =
      (struct BigInteger *)malloc(sizeof(struct BigInteger));
  if (temp == NULL)
  {
    return;
  }
  temp->data = key;
  temp->next = NULL;
  if ((*head) == NULL)
  {
    (*head) = temp;
    return;
  }
  struct BigInteger *iterator = (*head);
  while (iterator->next != NULL)
  {
    iterator = iterator->next;
  }
  iterator->next = temp;
}
struct BigInteger *initialize(char a[])
{
  struct BigInteger *head = NULL;
  int i = 0;
  int v = 0;
  while (a[i] != '\0')
  {
    v = (int)a[i] - 48;
    Tail(&head, v);
    i++;
  }
  return head;
}
void deletefromtail(struct BigInteger **head)
{
  struct BigInteger *temp = NULL;
  if (!(*head))
  {
    return;
  }
  if (!(*head)->next)
  {
    temp = *head;
    *head = NULL;
    free(temp);
    return;
  }
  struct BigInteger *iterator = *head;
  while (iterator->next->next != NULL)
  {
    iterator = iterator->next;
  }
  temp = iterator->next;
  iterator->next = NULL;
  free(temp);
}
void deletefromhead(struct BigInteger **head)
{
  struct BigInteger *temp = (*head);
  if (!(*head))
    return;
  (*head) = (*head)->next;
  free(temp);
}
void DisplayLL(struct BigInteger *head)
{
  while (head != NULL)
  {
    printf("%d->", head->data);
    head = head->next;
  }
}
void display(struct BigInteger *head)
{
  if (head == NULL)
  {
    return;
  }
  printf("%d", head->data);
  display(head->next);
}
void reverseLL(struct BigInteger **head)
{
  struct BigInteger *current_node = NULL;
  struct BigInteger *next = (*head)->next;
  (*head)->next = NULL;

  while (next != NULL)
  {
    current_node = next;
    next = next->next;
    current_node->next = (*head);
    (*head) = current_node;
  }
}
struct BigInteger *add(struct BigInteger *start1, struct BigInteger *start2)
{
  if (start1 == NULL)
    return start2;
  else if (start2 == NULL)
    return start1;
  reverseLL(&start1);
  reverseLL(&start2);
  struct BigInteger *h1 = start1;
  struct BigInteger *h2 = start2;
  struct BigInteger *add = NULL;
  int sum = 0;
  int carry = 0;
  while (start1 || start2)
  {
    sum = 0;
    if (start1)
      sum += start1->data;
    if (start2)
      sum += start2->data;
    sum += carry;
    carry = sum / 10;
    sum = sum % 10;
    Head(&add, sum);
    if (start1)
      start1 = start1->next;
    if (start2)
      start2 = start2->next;
  }
  if (carry)
    Head(&add, carry);
  reverseLL(&h1);
  reverseLL(&h2);
  return add;
}
struct BigInteger *Subtraction(struct BigInteger *start1, struct BigInteger *start2)
{
  reverseLL(&start1);
  reverseLL(&start2);
  struct BigInteger *h1 = start1;
  struct BigInteger *h2 = start2;
  struct BigInteger *subtract = NULL;
  int diff = 0;
  int borrow = 0;
  while (start1 || start2)
  {
    diff = 0;
    if (start1)
      diff += start1->data;
    if (start2)
      diff -= start2->data;
    diff -= borrow;
    if (diff < 0)
    {
      diff += 10;
      borrow = 1;
    }
    Head(&subtract, diff);
    if (start1)
      start1 = start1->next;
    if (start2)
      start2 = start2->next;
  }
  reverseLL(&h1);
  reverseLL(&h2);
  return subtract;
}
struct BigInteger *sub(struct BigInteger *start1, struct BigInteger *start2)
{
  struct BigInteger *subtract;
  if (calculate_len(start1) > calculate_len(start2))
  {
    subtract = Subtraction(start1, start2);
  }
  else if (calculate_len(start1) < calculate_len(start2))
  {
    subtract = Subtraction(start2, start1);
    subtract->data = -subtract->data;
  }
  else
  {
    if (comp(start1, start2) == 1)
    {
      subtract = Subtraction(start1, start2);
    }
    else if (comp(start1, start2) == -1)
    {
      subtract = Subtraction(start2, start1);
      subtract->data = -subtract->data;
    }
    else
    {
      subtract = (struct BigInteger *)malloc(sizeof(struct BigInteger));
      subtract->data = 0;
      subtract->next = NULL;
    }
  }
  return subtract;
}
struct BigInteger *mul(struct BigInteger *start1, struct BigInteger *start2)
{
  reverseLL(&start1);
  reverseLL(&start2);
  struct BigInteger *h1 = start1;
  struct BigInteger *h2 = start2;
  struct BigInteger *iterator = start1;
  struct BigInteger *add1 = NULL;
  struct BigInteger *add2 =
      (struct BigInteger *)malloc(sizeof(struct BigInteger));
  add2->data = 0;
  add2->next = NULL;
  struct BigInteger *add3 = NULL;
  int i = 0;
  int sum = 0;
  int carry = 0;
  while (start2)
  {
    while (iterator)
    {
      sum = 0;
      sum += iterator->data;
      sum *= start2->data;
      sum += carry;
      carry = sum / 10;
      sum = sum % 10;

      Head(&add1, sum);
      iterator = iterator->next;
    }
    if (carry)
      Head(&add1, carry);
    int n = i;

    while (n--)
    {
      Tail(&add1, 0);
    }
    add2 = add(add1, add2);
    add1 = NULL;
    iterator = start1;
    start2 = start2->next;
    i++;
  }
  reverseLL(&h1);
  reverseLL(&h2);
  return add2;
}
struct BigInteger *div1(struct BigInteger *start1, struct BigInteger *start2)
{
  if (greater(start1, start2) == -1)
  {
    struct BigInteger *div =
        (struct BigInteger *)malloc(sizeof(struct BigInteger));
    div->data = 0;
    div->next = NULL;
    return div;
  }
  int i = calculate_len(start1) - calculate_len(start2);

  struct BigInteger *div = NULL;
  int counter = 0;
  if (comp(start1, start2) == -1)
    i -= 1;

  for (int k = 0; k < i; k++)
  {
    Tail(&start2, 0);
  }

  while (i > -1)
  {
    i--;
    while (greater(start1, start2) == 1 || greater(start1, start2) == 0)
    {
      start1 = Subtraction(start1, start2);

      if (start1->data == 0)
      {
        deletefromhead(&start1);
      }
      counter++;
    }
    int c = counter % 10;
    Tail(&div, c);
    deletefromtail(&start2);
    counter = 0;
  }
  return div;
}